/*
    This file is part of KMail.
    SPDX-FileCopyrightText: 2003 Andreas Gungl <a.gungl@gmx.de>

    SPDX-License-Identifier: GPL-2.0-only
*/

#include "antispamwizard.h"
using namespace Qt::Literals::StringLiterals;

#include <KCursorSaver>
#include <MailCommon/FilterAction>
#include <MailCommon/FilterActionDict>
#include <MailCommon/FilterManager>
#include <MailCommon/FolderRequester>
#include <MailCommon/FolderTreeView>
#include <MailCommon/FolderTreeWidget>
#include <MailCommon/FolderTreeWidgetProxyModel>
#include <MailCommon/MailFilter>
#include <MailCommon/MailKernel>
#include <MailCommon/MailUtil>

#include <PimCommon/PimUtil>

#include <Akonadi/AgentInstance>

#include <KConfigGroup>
#include <KLocalizedString>
#include <KProcess>
#include <QDialog>

#include <KConfigGroup>
#include <MailCommon/ResourceReadConfigFile>
#include <QApplication>
#include <QBoxLayout>
#include <QCheckBox>
#include <QEventLoop>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
using namespace KMail;
using namespace MailCommon;

AntiSpamWizard::AntiSpamWizard(WizardMode mode, QWidget *parent)
    : KAssistantDialog(parent)
    , mInfoPage(nullptr)
    , mSpamRulesPage(nullptr)
    , mVirusRulesPage(nullptr)
    , mSummaryPage(nullptr)
    , mSpamToolsUsed(false)
    , mVirusToolsUsed(false)
    , mMode(mode)
{
    // read the configuration for the anti-spam tools
    ConfigReader reader(mMode, mToolList);
    reader.readAndMergeConfig();
    mToolList = reader.getToolList();
#ifndef NDEBUG
    if (mMode == AntiSpam) {
        qDebug() << "\nConsidered anti-spam tools:";
    } else {
        qDebug() << "\nConsidered anti-virus tools:";
    }
    QList<SpamToolConfig>::ConstIterator end(mToolList.constEnd());
    for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
        qDebug() << "Predefined tool:" << (*it).getId();
        qDebug() << "Config version:" << (*it).getVersion();
        qDebug() << "Selection priority:" << (*it).getPrio();
        qDebug() << "Displayed name:" << (*it).getVisibleName();
        qDebug() << "Executable:" << (*it).getExecutable();
        qDebug() << "WhatsThis URL:" << (*it).getWhatsThisText();
        qDebug() << "Filter name:" << (*it).getFilterName();
        qDebug() << "Detection command:" << (*it).getDetectCmd();
        qDebug() << "Learn spam command:" << (*it).getSpamCmd();
        qDebug() << "Learn ham command:" << (*it).getHamCmd();
        qDebug() << "Detection header:" << (*it).getDetectionHeader();
        qDebug() << "Detection pattern:" << (*it).getDetectionPattern();
        qDebug() << "Use as RegExp:" << (*it).isUseRegExp();
        qDebug() << "Supports Bayes Filter:" << (*it).useBayesFilter();
        qDebug() << "Type:" << (*it).getType();
    }
#endif

    const bool isAntiSpam = (mMode == AntiSpam);
    setWindowTitle(isAntiSpam ? i18nc("@title:window", "Anti-Spam Wizard") : i18nc("@title:window", "Anti-Virus Wizard"));
    mInfoPage = new ASWizInfoPage(mMode, nullptr, QString());
    mInfoPageItem = addPage(mInfoPage, isAntiSpam ? i18n("Welcome to the KMail Anti-Spam Wizard") : i18n("Welcome to the KMail Anti-Virus Wizard"));
    connect(mInfoPage, &ASWizInfoPage::selectionChanged, this, &AntiSpamWizard::checkProgramsSelections);

    if (isAntiSpam) {
        mSpamRulesPage = new ASWizSpamRulesPage(nullptr, QString());
        mSpamRulesPageItem = addPage(mSpamRulesPage, i18n("Options to fine-tune the handling of spam messages"));
        connect(mSpamRulesPage, &ASWizSpamRulesPage::selectionChanged, this, &AntiSpamWizard::slotBuildSummary);

        mSummaryPage = new ASWizSummaryPage(nullptr, QString());
        mSummaryPageItem = addPage(mSummaryPage, i18n("Summary of changes to be made by this wizard"));
    } else {
        mVirusRulesPage = new ASWizVirusRulesPage(nullptr, QString());
        mVirusRulesPageItem = addPage(mVirusRulesPage, i18n("Options to fine-tune the handling of virus messages"));
        connect(mVirusRulesPage, &ASWizVirusRulesPage::selectionChanged, this, &AntiSpamWizard::checkVirusRulesSelections);
    }

    connect(button(QDialogButtonBox::Help), &QPushButton::clicked, this, &AntiSpamWizard::slotHelpClicked);

    QTimer::singleShot(0, this, &AntiSpamWizard::checkToolAvailability);
}

void AntiSpamWizard::accept()
{
    if (mSpamRulesPage) {
        qDebug() << "Folder name for messages classified as spam is" << mSpamRulesPage->selectedSpamCollectionId();
        qDebug() << "Folder name for messages classified as unsure is" << mSpamRulesPage->selectedUnsureCollectionId();
    }
    if (mVirusRulesPage) {
        qDebug() << "Folder name for viruses is" << mVirusRulesPage->selectedFolderName();
    }

    FilterActionDict dict;
    QList<MailFilter *> filterList;
    bool replaceExistingFilters = false;

    // Let's start with virus detection and handling,
    // so we can avoid spam checks for viral messages
    if (mMode == AntiVirus) {
        if (!mVirusToolsUsed) {
            QDialog::accept();
            return;
        }
        QList<SpamToolConfig>::const_iterator end(mToolList.constEnd());
        for (QList<SpamToolConfig>::const_iterator it = mToolList.constBegin(); it != end; ++it) {
            if (mInfoPage->isProgramSelected((*it).getVisibleName()) && (mVirusRulesPage->pipeRulesSelected() && (*it).isVirusTool())) {
                // pipe messages through the anti-virus tools,
                // one single filter for each tool
                // (could get combined but so it's easier to understand for the user)
                auto pipeFilter = new MailFilter();
                QList<FilterAction *> *pipeFilterActions = pipeFilter->actions();
                FilterAction *pipeFilterAction = dict.value(u"filter app"_s)->create();
                pipeFilterAction->argsFromString((*it).getDetectCmd());
                pipeFilterActions->append(pipeFilterAction);
                SearchPattern *pipeFilterPattern = pipeFilter->pattern();
                pipeFilterPattern->setName(uniqueNameFor((*it).getFilterName()));
                pipeFilterPattern->append(SearchRule::createInstance("<size>", SearchRule::FuncIsGreaterOrEqual, u"0"_s));
                pipeFilter->setApplyOnOutbound(false);
                pipeFilter->setApplyOnInbound(true);
                pipeFilter->setApplyOnExplicit(true);
                pipeFilter->setStopProcessingHere(false);
                pipeFilter->setConfigureShortcut(false);

                filterList.append(pipeFilter);
            }
        }

        if (mVirusRulesPage->moveRulesSelected()) {
            // Sort out viruses depending on header fields set by the tools
            auto virusFilter = new MailFilter();
            QList<FilterAction *> *virusFilterActions = virusFilter->actions();
            FilterAction *virusFilterAction1 = dict.value(u"transfer"_s)->create();
            virusFilterAction1->argsFromString(mVirusRulesPage->selectedFolderName());
            virusFilterActions->append(virusFilterAction1);
            if (mVirusRulesPage->markReadRulesSelected()) {
                FilterAction *virusFilterAction2 = dict.value(u"set status"_s)->create();
                virusFilterAction2->argsFromString(u"R"_s); // Read
                virusFilterActions->append(virusFilterAction2);
            }
            SearchPattern *virusFilterPattern = virusFilter->pattern();
            virusFilterPattern->setName(uniqueNameFor(i18n("Virus handling")));
            virusFilterPattern->setOp(SearchPattern::OpOr);
            QList<SpamToolConfig>::ConstIterator endSpamTool(mToolList.constEnd());
            for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != endSpamTool; ++it) {
                if (mInfoPage->isProgramSelected((*it).getVisibleName())) {
                    if ((*it).isVirusTool()) {
                        const QByteArray header = (*it).getDetectionHeader().toLatin1();
                        const QString &pattern = (*it).getDetectionPattern();
                        if ((*it).isUseRegExp()) {
                            virusFilterPattern->append(SearchRule::createInstance(header, SearchRule::FuncRegExp, pattern));
                        } else {
                            virusFilterPattern->append(SearchRule::createInstance(header, SearchRule::FuncContains, pattern));
                        }
                    }
                }
            }
            virusFilter->setApplyOnOutbound(false);
            virusFilter->setApplyOnInbound(true);
            virusFilter->setApplyOnExplicit(true);
            virusFilter->setStopProcessingHere(true);
            virusFilter->setConfigureShortcut(false);

            filterList.append(virusFilter);
        }
    } else { // AntiSpam mode
        if (!mSpamToolsUsed) {
            QDialog::accept();
            return;
        }
        // TODO Existing filters with same name are replaced. This is hardcoded
        // ATM and needs to be replaced with a value from a (still missing)
        // checkbox in the GUI. At least, the replacement is announced in the GUI.
        replaceExistingFilters = true;
        QList<SpamToolConfig>::ConstIterator end(mToolList.constEnd());
        for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
            if (mInfoPage->isProgramSelected((*it).getVisibleName()) && (*it).isSpamTool() && !(*it).isDetectionOnly()) {
                // pipe messages through the anti-spam tools,
                // one single filter for each tool
                // (could get combined but so it's easier to understand for the user)
                auto pipeFilter = new MailFilter();
                QList<FilterAction *> *pipeFilterActions = pipeFilter->actions();
                FilterAction *pipeFilterAction = dict.value(u"filter app"_s)->create();
                pipeFilterAction->argsFromString((*it).getDetectCmd());
                pipeFilterActions->append(pipeFilterAction);
                SearchPattern *pipeFilterPattern = pipeFilter->pattern();
                if (replaceExistingFilters) {
                    pipeFilterPattern->setName((*it).getFilterName());
                } else {
                    pipeFilterPattern->setName(uniqueNameFor((*it).getFilterName()));
                }
                pipeFilterPattern->append(SearchRule::createInstance("<size>", SearchRule::FuncIsLessOrEqual, u"256000"_s));
                pipeFilter->setApplyOnOutbound(false);
                pipeFilter->setApplyOnInbound(true);
                pipeFilter->setApplyOnExplicit(true);
                pipeFilter->setStopProcessingHere(false);
                pipeFilter->setConfigureShortcut(false);

                filterList.append(pipeFilter);
            }
        }

        // Sort out spam depending on header fields set by the tools
        auto spamFilter = new MailFilter();
        QList<FilterAction *> *spamFilterActions = spamFilter->actions();
        if (mSpamRulesPage->moveSpamSelected()) {
            FilterAction *spamFilterAction1 = dict.value(u"transfer"_s)->create();
            spamFilterAction1->argsFromString(mSpamRulesPage->selectedSpamCollectionId());
            spamFilterActions->append(spamFilterAction1);
        }
        FilterAction *spamFilterAction2 = dict.value(u"set status"_s)->create();
        spamFilterAction2->argsFromString(u"P"_s); // Spam
        spamFilterActions->append(spamFilterAction2);
        if (mSpamRulesPage->markAsReadSelected()) {
            FilterAction *spamFilterAction3 = dict.value(u"set status"_s)->create();
            spamFilterAction3->argsFromString(u"R"_s); // Read
            spamFilterActions->append(spamFilterAction3);
        }
        SearchPattern *spamFilterPattern = spamFilter->pattern();
        if (replaceExistingFilters) {
            spamFilterPattern->setName(i18n("Spam Handling"));
        } else {
            spamFilterPattern->setName(uniqueNameFor(i18n("Spam Handling")));
        }
        spamFilterPattern->setOp(SearchPattern::OpOr);
        QList<SpamToolConfig>::ConstIterator endToolList(mToolList.constEnd());
        for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != endToolList; ++it) {
            if (mInfoPage->isProgramSelected((*it).getVisibleName())) {
                if ((*it).isSpamTool()) {
                    const QByteArray header = (*it).getDetectionHeader().toLatin1();
                    const QString &pattern = (*it).getDetectionPattern();
                    if ((*it).isUseRegExp()) {
                        spamFilterPattern->append(SearchRule::createInstance(header, SearchRule::FuncRegExp, pattern));
                    } else {
                        spamFilterPattern->append(SearchRule::createInstance(header, SearchRule::FuncContains, pattern));
                    }
                }
            }
        }
        spamFilter->setApplyOnOutbound(false);
        spamFilter->setApplyOnInbound(true);
        spamFilter->setApplyOnExplicit(true);
        spamFilter->setStopProcessingHere(true);
        spamFilter->setConfigureShortcut(false);
        filterList.append(spamFilter);

        if (mSpamRulesPage->moveUnsureSelected()) {
            // Sort out messages classified as unsure
            bool atLeastOneUnsurePattern = false;
            auto unsureFilter = new MailFilter();
            QList<FilterAction *> *unsureFilterActions = unsureFilter->actions();
            FilterAction *unsureFilterAction1 = dict.value(u"transfer"_s)->create();
            unsureFilterAction1->argsFromString(mSpamRulesPage->selectedUnsureCollectionId());
            unsureFilterActions->append(unsureFilterAction1);
            SearchPattern *unsureFilterPattern = unsureFilter->pattern();
            if (replaceExistingFilters) {
                unsureFilterPattern->setName(i18n("Semi spam (unsure) handling"));
            } else {
                unsureFilterPattern->setName(uniqueNameFor(i18n("Semi spam (unsure) handling")));
            }
            unsureFilterPattern->setOp(SearchPattern::OpOr);
            QList<SpamToolConfig>::ConstIterator end(mToolList.constEnd());
            for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
                if (mInfoPage->isProgramSelected((*it).getVisibleName())) {
                    if ((*it).isSpamTool() && (*it).hasTristateDetection()) {
                        atLeastOneUnsurePattern = true;
                        const QByteArray header = (*it).getDetectionHeader().toLatin1();
                        const QString &pattern = (*it).getDetectionPattern2();
                        if ((*it).isUseRegExp()) {
                            unsureFilterPattern->append(SearchRule::createInstance(header, SearchRule::FuncRegExp, pattern));
                        } else {
                            unsureFilterPattern->append(SearchRule::createInstance(header, SearchRule::FuncContains, pattern));
                        }
                    }
                }
            }
            unsureFilter->setApplyOnOutbound(false);
            unsureFilter->setApplyOnInbound(true);
            unsureFilter->setApplyOnExplicit(true);
            unsureFilter->setStopProcessingHere(true);
            unsureFilter->setConfigureShortcut(false);

            if (atLeastOneUnsurePattern) {
                filterList.append(unsureFilter);
            } else {
                delete unsureFilter;
            }
        }

        // Classify messages manually as Spam
        auto classSpamFilter = new MailFilter();
        classSpamFilter->setIcon(u"mail-mark-junk"_s);
        QList<FilterAction *> *classSpamFilterActions = classSpamFilter->actions();
        FilterAction *classSpamFilterActionFirst = dict.value(u"set status"_s)->create();
        classSpamFilterActionFirst->argsFromString(u"P"_s);
        classSpamFilterActions->append(classSpamFilterActionFirst);
        QList<SpamToolConfig>::ConstIterator endToolList2(mToolList.constEnd());
        for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != endToolList2; ++it) {
            if (mInfoPage->isProgramSelected((*it).getVisibleName()) && (*it).useBayesFilter() && !(*it).isDetectionOnly()) {
                FilterAction *classSpamFilterAction = dict.value(u"execute"_s)->create();
                classSpamFilterAction->argsFromString((*it).getSpamCmd());
                classSpamFilterActions->append(classSpamFilterAction);
            }
        }
        if (mSpamRulesPage->moveSpamSelected()) {
            FilterAction *classSpamFilterActionLast = dict.value(u"transfer"_s)->create();
            classSpamFilterActionLast->argsFromString(mSpamRulesPage->selectedSpamCollectionId());
            classSpamFilterActions->append(classSpamFilterActionLast);
        }

        SearchPattern *classSpamFilterPattern = classSpamFilter->pattern();
        if (replaceExistingFilters) {
            classSpamFilterPattern->setName(i18n("Classify as Spam"));
        } else {
            classSpamFilterPattern->setName(uniqueNameFor(i18n("Classify as Spam")));
        }
        classSpamFilterPattern->append(SearchRule::createInstance("<size>", SearchRule::FuncIsGreaterOrEqual, u"0"_s));
        classSpamFilter->setApplyOnOutbound(false);
        classSpamFilter->setApplyOnInbound(false);
        classSpamFilter->setApplyOnExplicit(false);
        classSpamFilter->setStopProcessingHere(true);
        classSpamFilter->setConfigureShortcut(true);
        classSpamFilter->setConfigureToolbar(true);
        classSpamFilter->setToolbarName(i18n("Spam"));
        filterList.append(classSpamFilter);

        // Classify messages manually as not Spam / as Ham
        auto classHamFilter = new MailFilter();
        classHamFilter->setIcon(u"mail-mark-notjunk"_s);
        QList<FilterAction *> *classHamFilterActions = classHamFilter->actions();
        FilterAction *classHamFilterActionFirst = dict.value(u"set status"_s)->create();
        classHamFilterActionFirst->argsFromString(u"H"_s);
        classHamFilterActions->append(classHamFilterActionFirst);
        end = mToolList.constEnd();
        for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
            if (mInfoPage->isProgramSelected((*it).getVisibleName()) && (*it).useBayesFilter() && !(*it).isDetectionOnly()) {
                FilterAction *classHamFilterAction = dict.value(u"execute"_s)->create();
                classHamFilterAction->argsFromString((*it).getHamCmd());
                classHamFilterActions->append(classHamFilterAction);
            }
        }
        end = mToolList.constEnd();
        for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
            if (mInfoPage->isProgramSelected((*it).getVisibleName()) && (*it).useBayesFilter() && !(*it).isDetectionOnly()) {
                FilterAction *classHamFilterAction = dict.value(u"filter app"_s)->create();
                classHamFilterAction->argsFromString((*it).getNoSpamCmd());
                classHamFilterActions->append(classHamFilterAction);
            }
        }
        SearchPattern *classHamFilterPattern = classHamFilter->pattern();
        if (replaceExistingFilters) {
            classHamFilterPattern->setName(i18n("Classify as NOT Spam"));
        } else {
            classHamFilterPattern->setName(uniqueNameFor(i18n("Classify as NOT Spam")));
        }
        classHamFilterPattern->append(SearchRule::createInstance("<size>", SearchRule::FuncIsGreaterOrEqual, u"0"_s));
        classHamFilter->setApplyOnOutbound(false);
        classHamFilter->setApplyOnInbound(false);
        classHamFilter->setApplyOnExplicit(false);
        classHamFilter->setStopProcessingHere(true);
        classHamFilter->setConfigureShortcut(true);
        classHamFilter->setConfigureToolbar(true);
        classHamFilter->setToolbarName(i18n("Ham"));
        filterList.append(classHamFilter);
    }

    /* Now that all the filters have been added to the list, tell
     * the filter manager about it. That will Q_EMIT filterListUpdate
     * which will result in the filter list in kmmainwidget being
     * initialized. This should happened only once. */
    if (!filterList.isEmpty()) {
        MailCommon::FilterManager::instance()->appendFilters(filterList, replaceExistingFilters);
    }

    QDialog::accept();
}

void AntiSpamWizard::checkProgramsSelections()
{
    bool supportUnsure = false;

    mSpamToolsUsed = false;
    mVirusToolsUsed = false;
    QList<SpamToolConfig>::ConstIterator end(mToolList.constEnd());
    for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
        if (mInfoPage->isProgramSelected((*it).getVisibleName())) {
            if ((*it).isSpamTool()) {
                mSpamToolsUsed = true;
                if ((*it).hasTristateDetection()) {
                    supportUnsure = true;
                }
            }
            if ((*it).isVirusTool()) {
                mVirusToolsUsed = true;
            }

            if (mSpamToolsUsed && mVirusToolsUsed && supportUnsure) {
                break;
            }
        }
    }

    if (mMode == AntiSpam) {
        mSpamRulesPage->allowUnsureFolderSelection(supportUnsure);
        mSpamRulesPage->allowMoveSpam(mSpamToolsUsed);
        slotBuildSummary();
        setAppropriate(mSpamRulesPageItem, mSpamToolsUsed);
        setAppropriate(mSummaryPageItem, mSpamToolsUsed);
    } else if (mMode == AntiVirus) {
        if (mVirusToolsUsed) {
            checkVirusRulesSelections();
        }
        setAppropriate(mVirusRulesPageItem, mVirusToolsUsed);
    }
}

void AntiSpamWizard::checkVirusRulesSelections()
{
    // setFinishEnabled( mVirusRulesPage, anyVirusOptionChecked() );
}

void AntiSpamWizard::checkToolAvailability()
{
    // this can take some time to find the tools
    KCursorSaver saver(Qt::WaitCursor);
    bool found = false;
    QList<SpamToolConfig>::ConstIterator end(mToolList.constEnd());
    for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
        const QString text(i18n("Scanning for %1…", (*it).getId()));
        mInfoPage->setScanProgressText(text);
        if ((*it).isSpamTool() && (*it).isServerBased()) {
            // check the configured account for pattern in <server>
            const QString pattern = (*it).getServerPattern();
            qDebug() << "Testing for server pattern:" << pattern;
            const Akonadi::AgentInstance::List lst = MailCommon::Util::agentInstances();
            for (const Akonadi::AgentInstance &type : lst) {
                if (type.status() == Akonadi::AgentInstance::Broken) {
                    continue;
                }
                const QString typeIdentifier(type.identifier());
                if (PimCommon::Util::isImapResource(typeIdentifier)) {
                    MailCommon::ResourceReadConfigFile resourceFile(typeIdentifier);
                    const KConfigGroup grp = resourceFile.group(u"network"_s);
                    if (grp.isValid()) {
                        const QString host = grp.readEntry(u"ImapServer"_s);
                        if (host.contains(pattern.toLower(), Qt::CaseInsensitive)) {
                            mInfoPage->addAvailableTool((*it).getVisibleName());
                            found = true;
                        }
                    }
                } else if (type.identifier().contains(POP3_RESOURCE_IDENTIFIER)) {
                    MailCommon::ResourceReadConfigFile resourceFile(typeIdentifier);
                    const KConfigGroup grp = resourceFile.group(u"General"_s);
                    if (grp.isValid()) {
                        const QString host = grp.readEntry(u"host"_s);
                        if (host.contains(pattern.toLower(), Qt::CaseInsensitive)) {
                            mInfoPage->addAvailableTool((*it).getVisibleName());
                            found = true;
                        }
                    }
                }
            }
        } else {
            // check the availability of the application
            qApp->processEvents(QEventLoop::ExcludeUserInputEvents, 200);
            if (!checkForProgram((*it).getExecutable())) {
                mInfoPage->addAvailableTool((*it).getVisibleName());
                found = true;
            }
        }
    }
    if (found) {
        mInfoPage->setScanProgressText((mMode == AntiSpam) ? i18n("Scanning for anti-spam tools finished.") : i18n("Scanning for anti-virus tools finished."));
    } else {
        mInfoPage->setScanProgressText((mMode == AntiSpam) ? i18n("<p>Sorry, no spam detection tools have been found. "
                                                                  "Install your spam detection software and "
                                                                  "re-run this wizard.</p>")
                                                           : i18n("Scanning complete. No anti-virus tools found."));
    }
    checkProgramsSelections();
}

void AntiSpamWizard::slotHelpClicked()
{
    PimCommon::Util::invokeHelp((mMode == AntiSpam) ? u"kmail2/the-anti-spam-wizard.html"_s : u"kmail2/the-anti-virus-wizard.html"_s);
}

void AntiSpamWizard::slotBuildSummary()
{
    QString text;
    QString newFilters;
    QString replaceFilters;

    if (mMode == AntiVirus) {
        text.clear(); // TODO add summary for the virus part
    } else { // AntiSpam mode
        if (mSpamRulesPage->markAsReadSelected()) {
            if (mSpamRulesPage->moveSpamSelected()) {
                text = i18n(
                    "<p>Messages classified as spam are marked as read."
                    "<br />Spam messages are moved into the folder named <i>%1</i>.</p>",
                    mSpamRulesPage->selectedSpamCollectionName());
            } else {
                text = i18n(
                    "<p>Messages classified as spam are marked as read."
                    "<br />Spam messages are not moved into a certain folder.</p>");
            }
        } else {
            if (mSpamRulesPage->moveSpamSelected()) {
                text = i18n(
                    "<p>Messages classified as spam are not marked as read."
                    "<br />Spam messages are moved into the folder named <i>%1</i>.</p>",
                    mSpamRulesPage->selectedSpamCollectionName());
            } else {
                text = i18n(
                    "<p>Messages classified as spam are not marked as read."
                    "<br />Spam messages are not moved into a certain folder.</p>");
            }
        }
        QList<SpamToolConfig>::ConstIterator end(mToolList.constEnd());
        for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
            if (mInfoPage->isProgramSelected((*it).getVisibleName()) && (*it).isSpamTool() && !(*it).isDetectionOnly()) {
                sortFilterOnExistance((*it).getFilterName(), newFilters, replaceFilters);
            }
        }
        sortFilterOnExistance(i18n("Spam Handling"), newFilters, replaceFilters);

        // The need for a handling of status "probably spam" depends on the tools chosen
        if (mSpamRulesPage->moveUnsureSelected()) {
            bool atLeastOneUnsurePattern = false;
            end = mToolList.constEnd();
            for (QList<SpamToolConfig>::ConstIterator it = mToolList.constBegin(); it != end; ++it) {
                if (mInfoPage->isProgramSelected((*it).getVisibleName())) {
                    if ((*it).isSpamTool() && (*it).hasTristateDetection()) {
                        atLeastOneUnsurePattern = true;
                        break;
                    }
                }
            }
            if (atLeastOneUnsurePattern) {
                sortFilterOnExistance(i18n("Semi spam (unsure) handling"), newFilters, replaceFilters);
                text +=
                    i18n("<p>The folder for messages classified as unsure (probably spam) is <i>%1</i>.</p>", mSpamRulesPage->selectedUnsureCollectionName());
            }
        }

        // Manual classification via toolbar icon / manually applied filter action
        sortFilterOnExistance(i18n("Classify as Spam"), newFilters, replaceFilters);
        sortFilterOnExistance(i18n("Classify as NOT Spam"), newFilters, replaceFilters);

        // Show the filters in the summary
        if (!newFilters.isEmpty()) {
            text += i18n("<p>The wizard will create the following filters:<ul>%1</ul></p>", newFilters);
        }
        if (!replaceFilters.isEmpty()) {
            text += i18n("<p>The wizard will replace the following filters:<ul>%1</ul></p>", replaceFilters);
        }
    }

    mSummaryPage->setSummaryText(text);
}

int AntiSpamWizard::checkForProgram(const QString &executable) const
{
    qDebug() << "Testing for executable:" << executable;
    KProcess process;
    process.setShellCommand(executable);
    return process.execute();
}

bool AntiSpamWizard::anyVirusOptionChecked() const
{
    return mVirusRulesPage->moveRulesSelected() || mVirusRulesPage->pipeRulesSelected();
}

const QString AntiSpamWizard::uniqueNameFor(const QString &name)
{
    return MailCommon::FilterManager::instance()->createUniqueFilterName(name);
}

void AntiSpamWizard::sortFilterOnExistance(const QString &intendedFilterName, QString &newFilters, QString &replaceFilters)
{
    if (uniqueNameFor(intendedFilterName) == intendedFilterName) {
        newFilters += QLatin1StringView("<li>") + intendedFilterName + QLatin1StringView("</li>");
    } else {
        replaceFilters += QLatin1StringView("<li>") + intendedFilterName + QLatin1StringView("</li>");
    }
}

//---------------------------------------------------------------------------
AntiSpamWizard::SpamToolConfig::SpamToolConfig(const QString &toolId,
                                               int configVersion,
                                               int prio,
                                               const QString &name,
                                               const QString &exec,
                                               const QString &url,
                                               const QString &filter,
                                               const QString &detection,
                                               const QString &spam,
                                               const QString &ham,
                                               const QString &noSpam,
                                               const QString &header,
                                               const QString &pattern,
                                               const QString &pattern2,
                                               const QString &serverPattern,
                                               bool detectionOnly,
                                               bool regExp,
                                               bool bayesFilter,
                                               bool tristateDetection,
                                               WizardMode type)
    : mId(toolId)
    , mVersion(configVersion)
    , mPrio(prio)
    , mVisibleName(name)
    , mExecutable(exec)
    , mWhatsThisText(url)
    , mFilterName(filter)
    , mDetectCmd(detection)
    , mSpamCmd(spam)
    , mHamCmd(ham)
    , mNoSpamCmd(noSpam)
    , mDetectionHeader(header)
    , mDetectionPattern(pattern)
    , mDetectionPattern2(pattern2)
    , mServerPattern(serverPattern)
    , mDetectionOnly(detectionOnly)
    , mUseRegExp(regExp)
    , mSupportsBayesFilter(bayesFilter)
    , mSupportsUnsure(tristateDetection)
    , mType(type)
{
}

int AntiSpamWizard::SpamToolConfig::getVersion() const
{
    return mVersion;
}

int AntiSpamWizard::SpamToolConfig::getPrio() const
{
    return mPrio;
}

QString AntiSpamWizard::SpamToolConfig::getId() const
{
    return mId;
}

QString AntiSpamWizard::SpamToolConfig::getVisibleName() const
{
    return mVisibleName;
}

QString AntiSpamWizard::SpamToolConfig::getExecutable() const
{
    return mExecutable;
}

QString AntiSpamWizard::SpamToolConfig::getWhatsThisText() const
{
    return mWhatsThisText;
}

QString AntiSpamWizard::SpamToolConfig::getFilterName() const
{
    return mFilterName;
}

QString AntiSpamWizard::SpamToolConfig::getDetectCmd() const
{
    return mDetectCmd;
}

QString AntiSpamWizard::SpamToolConfig::getSpamCmd() const
{
    return mSpamCmd;
}

QString AntiSpamWizard::SpamToolConfig::getHamCmd() const
{
    return mHamCmd;
}

QString AntiSpamWizard::SpamToolConfig::getNoSpamCmd() const
{
    return mNoSpamCmd;
}

QString AntiSpamWizard::SpamToolConfig::getDetectionHeader() const
{
    return mDetectionHeader;
}

QString AntiSpamWizard::SpamToolConfig::getDetectionPattern() const
{
    return mDetectionPattern;
}

QString AntiSpamWizard::SpamToolConfig::getDetectionPattern2() const
{
    return mDetectionPattern2;
}

QString AntiSpamWizard::SpamToolConfig::getServerPattern() const
{
    return mServerPattern;
}

bool AntiSpamWizard::SpamToolConfig::isServerBased() const
{
    return !mServerPattern.isEmpty();
}

bool AntiSpamWizard::SpamToolConfig::isDetectionOnly() const
{
    return mDetectionOnly;
}

bool AntiSpamWizard::SpamToolConfig::isUseRegExp() const
{
    return mUseRegExp;
}

bool AntiSpamWizard::SpamToolConfig::useBayesFilter() const
{
    return mSupportsBayesFilter;
}

bool AntiSpamWizard::SpamToolConfig::hasTristateDetection() const
{
    return mSupportsUnsure;
}

AntiSpamWizard::WizardMode AntiSpamWizard::SpamToolConfig::getType() const
{
    return mType;
}

bool AntiSpamWizard::SpamToolConfig::isSpamTool() const
{
    return mType == AntiSpam;
}

bool AntiSpamWizard::SpamToolConfig::isVirusTool() const
{
    return mType == AntiVirus;
}

//---------------------------------------------------------------------------
AntiSpamWizard::ConfigReader::ConfigReader(WizardMode mode, QList<SpamToolConfig> &configList)
    : mToolList(configList)
    , mMode(mode)
{
    if (mMode == AntiSpam) {
        mConfig = KSharedConfig::openConfig(u"kmail.antispamrc"_s);
    } else {
        mConfig = KSharedConfig::openConfig(u"kmail.antivirusrc"_s);
    }
}

AntiSpamWizard::ConfigReader::~ConfigReader() = default;

void AntiSpamWizard::ConfigReader::readAndMergeConfig()
{
    QString groupName = (mMode == AntiSpam) ? u"Spamtool #%1"_s : u"Virustool #%1"_s;
    // read the configuration from the global config file
    mConfig->setReadDefaults(true);
    KConfigGroup general(mConfig, u"General"_s);
    const int registeredTools = general.readEntry("tools", 0);
    for (int i = 1; i <= registeredTools; ++i) {
        KConfigGroup toolConfig(mConfig, groupName.arg(i));
        if (!toolConfig.readEntry("HeadersOnly", false)) {
            mToolList.append(readToolConfig(toolConfig));
        }
    }

    // read the configuration from the user config file
    // and merge newer config data
    mConfig->setReadDefaults(false);
    KConfigGroup user_general(mConfig, u"General"_s);
    const int user_registeredTools = user_general.readEntry("tools", 0);
    for (int i = 1; i <= user_registeredTools; ++i) {
        KConfigGroup toolConfig(mConfig, groupName.arg(i));
        if (!toolConfig.readEntry("HeadersOnly", false)) {
            mergeToolConfig(readToolConfig(toolConfig));
        }
    }
    // Make sure to have add least one tool listed even when the
    // config file was not found or whatever went wrong
    // Currently only works for spam tools
    if (mMode == AntiSpam) {
        if (registeredTools < 1 && user_registeredTools < 1) {
            mToolList.append(createDummyConfig());
        }
        sortToolList();
    }
}

AntiSpamWizard::SpamToolConfig AntiSpamWizard::ConfigReader::readToolConfig(KConfigGroup &configGroup)
{
    const QString id = configGroup.readEntry("Ident");
    const int version = configGroup.readEntry("Version", 0);
#ifndef NDEBUG
    qDebug() << "Found predefined tool:" << id;
    qDebug() << "With config version  :" << version;
#endif
    const int prio = configGroup.readEntry("Priority", 1);
    const QString name = configGroup.readEntry("VisibleName");
    const QString executable = configGroup.readEntry("Executable");
    const QString url = configGroup.readEntry("URL");
    const QString filterName = configGroup.readEntry("PipeFilterName");
    const QString detectCmd = configGroup.readEntry("PipeCmdDetect");
    const QString spamCmd = configGroup.readEntry("ExecCmdSpam");
    const QString hamCmd = configGroup.readEntry("ExecCmdHam");
    const QString noSpamCmd = configGroup.readEntry("PipeCmdNoSpam");
    const QString header = configGroup.readEntry("DetectionHeader");
    const QString pattern = configGroup.readEntry("DetectionPattern");
    const QString pattern2 = configGroup.readEntry("DetectionPattern2");
    const QString serverPattern = configGroup.readEntry("ServerPattern");
    const bool detectionOnly = configGroup.readEntry("DetectionOnly", false);
    const bool useRegExp = configGroup.readEntry("UseRegExp", false);
    const bool supportsBayes = configGroup.readEntry("SupportsBayes", false);
    const bool supportsUnsure = configGroup.readEntry("SupportsUnsure", false);
    return SpamToolConfig(id,
                          version,
                          prio,
                          name,
                          executable,
                          url,
                          filterName,
                          detectCmd,
                          spamCmd,
                          hamCmd,
                          noSpamCmd,
                          header,
                          pattern,
                          pattern2,
                          serverPattern,
                          detectionOnly,
                          useRegExp,
                          supportsBayes,
                          supportsUnsure,
                          mMode);
}

AntiSpamWizard::SpamToolConfig AntiSpamWizard::ConfigReader::createDummyConfig()
{
    return SpamToolConfig(u"spamassassin"_s,
                          0,
                          1,
                          u"SpamAssassin"_s,
                          u"spamassassin -V"_s,
                          u"https://spamassassin.apache.org/"_s,
                          u"SpamAssassin Check"_s,
                          u"spamassassin -L"_s,
                          u"sa-learn -L --spam --no-sync --single"_s,
                          u"sa-learn -L --ham --no-sync --single"_s,
                          u"spamassassin -d"_s,
                          u"X-Spam-Status"_s,
                          u"yes"_s,
                          QString(),
                          QString(),
                          false,
                          false,
                          true,
                          false,
                          AntiSpam);
}

void AntiSpamWizard::ConfigReader::mergeToolConfig(const AntiSpamWizard::SpamToolConfig &config)
{
    bool found = false;
    QList<SpamToolConfig>::Iterator end(mToolList.end());
    for (QList<SpamToolConfig>::Iterator it = mToolList.begin(); it != end; ++it) {
#ifndef NDEBUG
        qDebug() << "Check against tool:" << (*it).getId();
        qDebug() << "Against version   :" << (*it).getVersion();
#endif
        if ((*it).getId() == config.getId()) {
            found = true;
            if ((*it).getVersion() < config.getVersion()) {
#ifndef NDEBUG
                qDebug() << "Replacing config ...";
#endif
                mToolList.erase(it);
                mToolList.append(config);
            }
            break;
        }
    }
    if (!found) {
        mToolList.append(config);
    }
}

void AntiSpamWizard::ConfigReader::sortToolList()
{
    QList<SpamToolConfig> tmpList;
    SpamToolConfig config;

    while (!mToolList.isEmpty()) {
        QList<SpamToolConfig>::Iterator highest;
        int priority = 0; // ascending
        QList<SpamToolConfig>::Iterator end(mToolList.end());
        for (QList<SpamToolConfig>::Iterator it = mToolList.begin(); it != end; ++it) {
            if ((*it).getPrio() > priority) {
                priority = (*it).getPrio();
                highest = it;
            }
        }
        config = (*highest);
        tmpList.append(config);
        mToolList.erase(highest);
    }
    QList<SpamToolConfig>::ConstIterator end(tmpList.constEnd());
    for (QList<SpamToolConfig>::ConstIterator it = tmpList.constBegin(); it != end; ++it) {
        mToolList.append((*it));
    }
}

//---------------------------------------------------------------------------
ASWizPage::ASWizPage(QWidget *parent, const QString &name)
    : QWidget(parent)
{
    setObjectName(name);
    mLayout = new QHBoxLayout(this);

    auto sideLayout = new QVBoxLayout();
    mLayout->addItem(sideLayout);
    mLayout->addItem(new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QPixmap banner;
    banner.load(u":/org/kde/kmail/pics/kmwizard.png"_s);
    auto bannerLabel = new QLabel(this);
    bannerLabel->setPixmap(banner);
    bannerLabel->setScaledContents(false);
    bannerLabel->setFrameShape(QFrame::StyledPanel);
    bannerLabel->setFrameShadow(QFrame::Sunken);
    bannerLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    sideLayout->addWidget(bannerLabel);
    sideLayout->addItem(new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

//---------------------------------------------------------------------------
ASWizInfoPage::ASWizInfoPage(AntiSpamWizard::WizardMode mode, QWidget *parent, const QString &name)
    : ASWizPage(parent, name)
{
    QBoxLayout *layout = new QVBoxLayout();
    mLayout->addItem(layout);

    auto introText = new QTextEdit(this);
    introText->setText((mode == AntiSpamWizard::AntiSpam) ? i18n("The wizard will search for any tools to do spam detection\n"
                                                                 "and setup KMail to work with them.")
                                                          : i18n("<p>Here you can get some assistance in setting up KMail's filter "
                                                                 "rules to use some commonly-known anti-virus tools.</p>"
                                                                 "<p>The wizard can detect those tools on your computer as "
                                                                 "well as create filter rules to classify messages using these "
                                                                 "tools and to separate messages containing viruses. "
                                                                 "The wizard will not take any existing filter "
                                                                 "rules into consideration: it will always append the new rules.</p>"
                                                                 "<p><b>Warning:</b> As KMail appears to be frozen during the scan of the "
                                                                 "messages for viruses, you may encounter problems with "
                                                                 "the responsiveness of KMail because anti-virus tool "
                                                                 "operations are usually time consuming; please consider "
                                                                 "deleting the filter rules created by the wizard to get "
                                                                 "back to the former behavior.</p>"));
    introText->setReadOnly(true);
    introText->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addWidget(introText);

    mScanProgressText = new QLabel(this);
    mScanProgressText->clear();
    mScanProgressText->setWordWrap(true);
    layout->addWidget(mScanProgressText);

    mToolsList = new QListWidget(this);
    mToolsList->hide();
    mToolsList->setSelectionMode(QAbstractItemView::MultiSelection);
    mToolsList->setLayoutMode(QListView::Batched);
    mToolsList->setBatchSize(10);
    mToolsList->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum));
    layout->addWidget(mToolsList);
    connect(mToolsList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ASWizInfoPage::processSelectionChange);

    mSelectionHint = new QLabel(this);
    mSelectionHint->clear();
    mSelectionHint->setWordWrap(true);
    layout->addWidget(mSelectionHint);
}

void ASWizInfoPage::setScanProgressText(const QString &toolName)
{
    mScanProgressText->setText(toolName);
}

void ASWizInfoPage::addAvailableTool(const QString &visibleName)
{
    mToolsList->addItem(visibleName);
    if (!mToolsList->isVisible()) {
        mToolsList->show();
        mToolsList->selectionModel()->clearSelection();
        mToolsList->setCurrentRow(0);
        mSelectionHint->setText(
            i18n("<p>Please select the tools to be used "
                 "for the detection and go "
                 "to the next page.</p>"));
    }
}

bool ASWizInfoPage::isProgramSelected(const QString &visibleName) const
{
    const QList<QListWidgetItem *> foundItems = mToolsList->findItems(visibleName, Qt::MatchFixedString);
    return !foundItems.isEmpty() && foundItems[0]->isSelected();
}

void ASWizInfoPage::processSelectionChange()
{
    Q_EMIT selectionChanged();
}

//---------------------------------------------------------------------------
ASWizSpamRulesPage::ASWizSpamRulesPage(QWidget *parent, const QString &name)
    : ASWizPage(parent, name)
{
    auto layout = new QVBoxLayout();
    mLayout->addItem(layout);

    mMarkRules = new QCheckBox(i18nc("@option:check", "&Mark detected spam messages as read"), this);
    mMarkRules->setWhatsThis(i18n("Mark messages which have been classified as spam as read."));
    layout->addWidget(mMarkRules);

    mMoveSpamRules = new QCheckBox(i18nc("@option:check", "Move &known spam to:"), this);
    mMoveSpamRules->setWhatsThis(
        i18n("The default folder for spam messages is the trash folder, "
             "but you may change that in the folder view below."));
    layout->addWidget(mMoveSpamRules);

    mFolderReqForSpamFolder = new FolderRequester(this);
    mFolderReqForSpamFolder->setCollection(CommonKernel->trashCollectionFolder());
    mFolderReqForSpamFolder->setMustBeReadWrite(true);
    mFolderReqForSpamFolder->setShowOutbox(false);

    auto hLayout1 = new QHBoxLayout();
    layout->addItem(hLayout1);
    hLayout1->addWidget(mFolderReqForSpamFolder);

    mMoveUnsureRules = new QCheckBox(i18nc("@option:check", "Move &probable spam to:"), this);
    mMoveUnsureRules->setWhatsThis(
        i18n("The default folder is the inbox folder, but you may change that "
             "in the folder view below.<p>"
             "Not all tools support a classification as unsure. If you have not "
             "selected a capable tool, you cannot select a folder as well.</p>"));
    layout->addWidget(mMoveUnsureRules);

    mFolderReqForUnsureFolder = new FolderRequester(this);
    mFolderReqForUnsureFolder->setCollection(CommonKernel->inboxCollectionFolder());
    mFolderReqForUnsureFolder->setMustBeReadWrite(true);
    mFolderReqForUnsureFolder->setShowOutbox(false);

    auto hLayout2 = new QHBoxLayout();
    layout->addItem(hLayout2);
    hLayout2->addWidget(mFolderReqForUnsureFolder);

    layout->addStretch();

    connect(mMarkRules, &QAbstractButton::clicked, this, &ASWizSpamRulesPage::processSelectionChange);
    connect(mMoveSpamRules, &QAbstractButton::clicked, this, &ASWizSpamRulesPage::processSelectionChange);
    connect(mMoveUnsureRules, &QAbstractButton::clicked, this, &ASWizSpamRulesPage::processSelectionChange);
    connect(mFolderReqForSpamFolder, &FolderRequester::folderChanged, this, &ASWizSpamRulesPage::processSelectionChange);
    connect(mFolderReqForUnsureFolder, &FolderRequester::folderChanged, this, &ASWizSpamRulesPage::processSelectionChange);

    mMarkRules->setChecked(true);
    mMoveSpamRules->setChecked(true);
}

bool ASWizSpamRulesPage::markAsReadSelected() const
{
    return mMarkRules->isChecked();
}

bool ASWizSpamRulesPage::moveSpamSelected() const
{
    return mMoveSpamRules->isChecked();
}

bool ASWizSpamRulesPage::moveUnsureSelected() const
{
    return mMoveUnsureRules->isChecked();
}

QString ASWizSpamRulesPage::selectedSpamCollectionId() const
{
    return QString::number(selectedSpamCollection().id());
}

QString ASWizSpamRulesPage::selectedSpamCollectionName() const
{
    return selectedSpamCollection().name();
}

Akonadi::Collection ASWizSpamRulesPage::selectedSpamCollection() const
{
    if (mFolderReqForSpamFolder->hasCollection()) {
        return mFolderReqForSpamFolder->collection();
    } else {
        return CommonKernel->trashCollectionFolder();
    }
}

Akonadi::Collection ASWizSpamRulesPage::selectedUnsureCollection() const
{
    if (mFolderReqForUnsureFolder->hasCollection()) {
        return mFolderReqForUnsureFolder->collection();
    } else {
        return CommonKernel->inboxCollectionFolder();
    }
}

QString ASWizSpamRulesPage::selectedUnsureCollectionName() const
{
    return selectedUnsureCollection().name();
}

QString ASWizSpamRulesPage::selectedUnsureCollectionId() const
{
    return QString::number(selectedUnsureCollection().id());
}

void ASWizSpamRulesPage::processSelectionChange()
{
    mFolderReqForSpamFolder->setEnabled(mMoveSpamRules->isChecked());
    mFolderReqForUnsureFolder->setEnabled(mMoveUnsureRules->isChecked());
    Q_EMIT selectionChanged();
}

void ASWizSpamRulesPage::allowUnsureFolderSelection(bool enabled)
{
    mMoveUnsureRules->setEnabled(enabled);
    mMoveUnsureRules->setVisible(enabled);
    mFolderReqForUnsureFolder->setEnabled(enabled);
    mFolderReqForUnsureFolder->setVisible(enabled);
}

void ASWizSpamRulesPage::allowMoveSpam(bool enabled)
{
    mMarkRules->setEnabled(enabled);
    mMarkRules->setChecked(enabled);
    mMoveSpamRules->setEnabled(enabled);
    mMoveSpamRules->setChecked(enabled);
}

//---------------------------------------------------------------------------
ASWizVirusRulesPage::ASWizVirusRulesPage(QWidget *parent, const QString &name)
    : ASWizPage(parent, name)
{
    auto grid = new QGridLayout();
    mLayout->addItem(grid);

    mPipeRules = new QCheckBox(i18nc("@option:check", "Check messages using the anti-virus tools"), this);
    mPipeRules->setWhatsThis(
        i18n("Let the anti-virus tools check your messages. The wizard "
             "will create appropriate filters. The messages are usually "
             "marked by the tools so that following filters can react "
             "on this and, for example, move virus messages to a special folder."));
    grid->addWidget(mPipeRules, 0, 0);

    mMoveRules = new QCheckBox(i18nc("@option:check", "Move detected viral messages to the selected folder"), this);
    mMoveRules->setWhatsThis(
        i18n("A filter to detect messages classified as virus-infected and to move "
             "those messages into a predefined folder is created. The "
             "default folder is the trash folder, but you may change that "
             "in the folder view."));
    grid->addWidget(mMoveRules, 1, 0);

    mMarkRules = new QCheckBox(i18nc("@option:check", "Additionally, mark detected viral messages as read"), this);
    mMarkRules->setEnabled(false);
    mMarkRules->setWhatsThis(
        i18n("Mark messages which have been classified as "
             "virus-infected as read, as well as moving them "
             "to the selected folder."));
    grid->addWidget(mMarkRules, 2, 0);
    FolderTreeWidget::TreeViewOptions opt = FolderTreeWidget::None;
    opt |= FolderTreeWidget::UseDistinctSelectionModel;

    FolderTreeWidgetProxyModel::FolderTreeWidgetProxyModelOptions optReadableProxy = FolderTreeWidgetProxyModel::None;
    optReadableProxy |= FolderTreeWidgetProxyModel::HideVirtualFolder;
    optReadableProxy |= FolderTreeWidgetProxyModel::HideOutboxFolder;

    mFolderTree = new FolderTreeWidget(this, nullptr, opt, optReadableProxy);
    mFolderTree->readConfig();
    mFolderTree->folderTreeView()->expandAll();
    mFolderTree->folderTreeWidgetProxyModel()->setAccessRights(Akonadi::Collection::CanCreateCollection);

    mFolderTree->selectCollectionFolder(CommonKernel->trashCollectionFolder());
    mFolderTree->folderTreeView()->setDragDropMode(QAbstractItemView::NoDragDrop);

    mFolderTree->disableContextMenuAndExtraColumn();
    grid->addWidget(mFolderTree, 3, 0);

    connect(mPipeRules, &QCheckBox::clicked, this, &ASWizVirusRulesPage::processSelectionChange);
    connect(mMoveRules, &QCheckBox::clicked, this, &ASWizVirusRulesPage::processSelectionChange);
    connect(mMarkRules, &QCheckBox::clicked, this, &ASWizVirusRulesPage::processSelectionChange);
    connect(mMoveRules, &QCheckBox::toggled, mMarkRules, &QCheckBox::setEnabled);
}

bool ASWizVirusRulesPage::pipeRulesSelected() const
{
    return mPipeRules->isChecked();
}

bool ASWizVirusRulesPage::moveRulesSelected() const
{
    return mMoveRules->isChecked();
}

bool ASWizVirusRulesPage::markReadRulesSelected() const
{
    return mMarkRules->isChecked();
}

QString ASWizVirusRulesPage::selectedFolderName() const
{
    if (mFolderTree->selectedCollection().isValid()) {
        return QString::number(mFolderTree->selectedCollection().id());
    } else {
        return QString::number(CommonKernel->trashCollectionFolder().id());
    }
}

void ASWizVirusRulesPage::processSelectionChange()
{
    Q_EMIT selectionChanged();
}

//---------------------------------------------------------------------------
ASWizSummaryPage::ASWizSummaryPage(QWidget *parent, const QString &name)
    : ASWizPage(parent, name)
    , mSummaryText(new QLabel(this))
{
    QBoxLayout *layout = new QVBoxLayout();
    mLayout->addItem(layout);

    layout->addWidget(mSummaryText);
    layout->addStretch();
}

void ASWizSummaryPage::setSummaryText(const QString &text)
{
    mSummaryText->setText(text);
}

#include "moc_antispamwizard.cpp"
