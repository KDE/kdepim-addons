/* ============================================================
*
* This file is a part of the rekonq project
*
* Copyright (c) 2013-2016 Montel Laurent <montel@kde.org>
* based on code from rekonq
* Copyright (C) 2010-2012 by Andrea Diamantini <adjam7 at gmail dot com>
*
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License as
* published by the Free Software Foundation; either version 2 of
* the License or (at your option) version 3 or any later version
* accepted by the membership of KDE e.V. (or its successor approved
* by the membership of KDE e.V.), which shall act as a proxy
* defined in Section 14 of version 3 of the license.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* ============================================================ */

// Self Includes
#include "adblocksettingwidget.h"
#include "ui_settings_adblock.h"
#include "globalsettings_webengineurlinterceptoradblock.h"
#include "adblockaddsubscriptiondialog.h"

//#include "adblock/adblockmanager.h"
#include "adblockshowlistdialog.h"
#include "adblockutil.h"
#include "PimCommon/ConfigureImmutableWidgetUtils"
using namespace PimCommon::ConfigureImmutableWidgetUtils;

#include "PimCommon/PimUtil"

// KDE Includes
#include <KSharedConfig>

#include <QIcon>

#include <KMessageBox>
#include <KLocalizedString>
#include <QWhatsThisClickedEvent>

// Qt Includes
#include <QWhatsThis>
#include <QListWidgetItem>
#include <QFile>
#include <QPointer>
#include <QTextStream>
#include <QStandardPaths>
#include <QRegularExpression>
#include <KRun>

using namespace AdBlock;
AdBlockSettingWidget::AdBlockSettingWidget(QWidget *parent)
    : QWidget(parent)
    , mChanged(false)
{
    mUi = new Ui::adblock;
    mUi->setupUi(this);

    mUi->hintLabel->setText(i18n("<qt>Filter expression (e.g. <tt>http://www.example.com/ad/*</tt>, <a href=\"filterhelp\">more information</a>):"));
    connect(mUi->hintLabel, &QLabel::linkActivated, this, &AdBlockSettingWidget::slotInfoLinkActivated);
    mUi->hintLabel->setContextMenuPolicy(Qt::NoContextMenu);

    mUi->manualFiltersListWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    mUi->searchLine->setListWidget(mUi->manualFiltersListWidget);

    mUi->insertButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    connect(mUi->insertButton, &QToolButton::clicked, this, &AdBlockSettingWidget::insertRule);

    mUi->removeButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    connect(mUi->removeButton, &QPushButton::clicked, this, &AdBlockSettingWidget::removeRule);
    connect(mUi->removeSubscription, &QPushButton::clicked, this, &AdBlockSettingWidget::slotRemoveSubscription);
    connect(mUi->manualFiltersListWidget, &QListWidget::currentItemChanged, this, &AdBlockSettingWidget::slotUpdateManualButtons);
    connect(mUi->manualFiltersListWidget, &QListWidget::itemChanged, this, &AdBlockSettingWidget::hasChanged);

    mUi->spinBox->setSuffix(ki18np(" day", " days"));

    mUi->removeSubscription->setEnabled(false);
    mUi->showList->setEnabled(false);
    // Q_EMIT changed signal
    connect(mUi->checkEnableAdblock, &QCheckBox::stateChanged, this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->checkHideAds, &QCheckBox::stateChanged, this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->spinBox, static_cast<void (KPluralHandlingSpinBox::*)(int)>(&KPluralHandlingSpinBox::valueChanged), this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->addFilters, &QPushButton::clicked, this, &AdBlockSettingWidget::slotAddFilter);
    connect(mUi->showList, &QPushButton::clicked, this, &AdBlockSettingWidget::slotShowList);
    connect(mUi->editFilter, &QPushButton::clicked, this, &AdBlockSettingWidget::slotEditFilter);

    connect(mUi->automaticFiltersListWidget, &AdBlock::AdBlockListWidget::itemChanged, this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->automaticFiltersListWidget, &AdBlock::AdBlockListWidget::currentItemChanged, this, &AdBlockSettingWidget::slotUpdateButtons);
    connect(mUi->automaticFiltersListWidget, &AdBlock::AdBlockListWidget::itemDoubleClicked, this, &AdBlockSettingWidget::slotAutomaticFilterDouble);

    connect(mUi->importFilters, &QPushButton::clicked, this, &AdBlockSettingWidget::slotImportFilters);
    connect(mUi->exportFilters, &QPushButton::clicked, this, &AdBlockSettingWidget::slotExportFilters);
    connect(mUi->addFilterLineEdit, &QLineEdit::textChanged, this, &AdBlockSettingWidget::slotManualFilterLineEditTextChanged);
    slotUpdateManualButtons();
    mUi->insertButton->setEnabled(false);
}

AdBlockSettingWidget::~AdBlockSettingWidget()
{
    delete mUi;
}

void AdBlockSettingWidget::slotManualFilterLineEditTextChanged(const QString &text)
{
    mUi->insertButton->setEnabled(!text.isEmpty());
}

void AdBlockSettingWidget::slotEditFilter()
{
    QListWidgetItem *item = mUi->manualFiltersListWidget->currentItem();
    if (item) {
        mUi->manualFiltersListWidget->editItem(item);
    }
}

void AdBlockSettingWidget::slotUpdateButtons()
{
    const bool enabled = mUi->automaticFiltersListWidget->currentItem();
    mUi->removeSubscription->setEnabled(enabled);
    mUi->showList->setEnabled(enabled);
}

void AdBlockSettingWidget::slotUpdateManualButtons()
{
    const bool enabled = mUi->manualFiltersListWidget->currentItem();
    mUi->removeButton->setEnabled(enabled);
    mUi->editFilter->setEnabled(enabled);
    mUi->exportFilters->setEnabled(mUi->manualFiltersListWidget->count() > 0);
}

void AdBlockSettingWidget::slotInfoLinkActivated(const QString &url)
{
    Q_UNUSED(url)

    const QString href = QStringLiteral("https://adblockplus.org/en/filters");
    const QString hintHelpString = i18n("<qt><p>Enter an expression to filter. Filters can be defined as either:"
                                        "<ul><li>a shell-style wildcard, e.g. <tt>http://www.example.com/ads*</tt>, "
                                        "the wildcards <tt>*?[]</tt> may be used</li>"
                                        "<li>a full regular expression by surrounding the string with '<tt>/</tt>', "
                                        "e.g. <tt>/\\/(ad|banner)\\./</tt></li></ul>"
                                        "<p>Any filter string can be preceded by '<tt>@@</tt>' to whitelist (allow) any matching URL, "
                                        "which takes priority over any blacklist (blocking) filter.<br><a href=\'%1\'>%2</a></qt>", href, i18n("More information"));

    QWhatsThis::showText(QCursor::pos(), hintHelpString, this);
}

bool AdBlockSettingWidget::event(QEvent *event)
{
    if (event->type() == QEvent::WhatsThisClicked) {
        QWhatsThisClickedEvent *clicked = static_cast<QWhatsThisClickedEvent *>(event);
        new KRun(QUrl(clicked->href()), this);
        return true;
    }
    return QWidget::event(event);
}

void AdBlockSettingWidget::insertRule()
{
    const QString rule = mUi->addFilterLineEdit->text();
    if (rule.isEmpty()) {
        return;
    }
    const int numberItem(mUi->manualFiltersListWidget->count());
    for (int i = 0; i < numberItem; ++i) {
        if (mUi->manualFiltersListWidget->item(i)->text() == rule) {
            mUi->addFilterLineEdit->clear();
            return;
        }
    }

    addManualFilter(rule);
    mUi->exportFilters->setEnabled(mUi->manualFiltersListWidget->count() > 0);
    mUi->addFilterLineEdit->clear();
    hasChanged();
}

void AdBlockSettingWidget::removeRule()
{
    QList<QListWidgetItem *> select = mUi->manualFiltersListWidget->selectedItems();
    if (select.isEmpty()) {
        return;
    }
    Q_FOREACH (QListWidgetItem *item, select) {
        delete item;
    }
    mUi->exportFilters->setEnabled(mUi->manualFiltersListWidget->count() > 0);
    hasChanged();
}

void AdBlockSettingWidget::doResetToDefaultsOther()
{
    const bool bUseDefaults = AdBlock::AdBlockSettings::self()->useDefaults(true);
    loadWidget(mUi->checkEnableAdblock, AdBlock::AdBlockSettings::self()->adBlockEnabledItem());
    mUi->tabWidget->setEnabled(AdBlock::AdBlockSettings::self()->adBlockEnabled());
    saveCheckBox(mUi->checkHideAds, AdBlock::AdBlockSettings::self()->hideAdsEnabledItem());
    loadWidget(mUi->spinBox, AdBlock::AdBlockSettings::self()->adBlockUpdateIntervalItem());
    AdBlock::AdBlockSettings::self()->useDefaults(bUseDefaults);
}

void AdBlockSettingWidget::doLoadFromGlobalSettings()
{
    mUi->manualFiltersListWidget->clear();
    mUi->automaticFiltersListWidget->clear();
    loadWidget(mUi->checkEnableAdblock, AdBlock::AdBlockSettings::self()->adBlockEnabledItem());

    // update enabled status
    mUi->tabWidget->setEnabled(AdBlock::AdBlockSettings::self()->adBlockEnabled());
    loadWidget(mUi->checkHideAds, AdBlock::AdBlockSettings::self()->hideAdsEnabledItem());
    loadWidget(mUi->spinBox, AdBlock::AdBlockSettings::self()->adBlockUpdateIntervalItem());
    // ------------------------------------------------------------------------------

    // automatic filters
    KConfig config(QStringLiteral("AdBlockadblockrc"));

    const QStringList itemList = config.groupList().filter(QRegularExpression(QStringLiteral("FilterList \\d+")));
    Q_FOREACH (const QString &item, itemList) {
        KConfigGroup filtersGroup(&config, item);
        const bool isFilterEnabled = filtersGroup.readEntry(QStringLiteral("FilterEnabled"), false);
        const QString url = filtersGroup.readEntry(QStringLiteral("url"));
        const QString path = filtersGroup.readEntry(QStringLiteral("path"));
        const QString name = filtersGroup.readEntry(QStringLiteral("name"));
        const QDateTime lastUpdate = filtersGroup.readEntry(QStringLiteral("lastUpdate"), QDateTime());
        if (url.isEmpty() || path.isEmpty() || name.isEmpty()) {
            continue;
        }

        QListWidgetItem *subItem = new QListWidgetItem(mUi->automaticFiltersListWidget);
        subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
        if (isFilterEnabled) {
            subItem->setCheckState(Qt::Checked);
        } else {
            subItem->setCheckState(Qt::Unchecked);
        }

        subItem->setData(UrlList, url);
        subItem->setData(PathList, path);
        subItem->setData(LastUpdateList, lastUpdate);
        subItem->setText(name);
    }

    // ------------------------------------------------------------------------------

    // local filters
    const QString localRulesFilePath = AdBlock::AdBlockUtil::localFilterPath();

    QFile ruleFile(localRulesFilePath);
    if (!ruleFile.open(QFile::ReadOnly | QFile::Text)) {
        //FIXME qCDebug(AdBlock_LOG) << "Unable to open rule file" << localRulesFilePath;
        return;
    }

    KConfigGroup grp = config.group(QStringLiteral("DisableRules"));
    const QStringList disableRules = grp.readEntry("DisableRules", QStringList());

    QTextStream in(&ruleFile);
    while (!in.atEnd()) {
        QString stringRule = in.readLine();
        addManualFilter(stringRule, disableRules);
    }
    updateCheckBox();
}

void AdBlockSettingWidget::save()
{
    if (!mChanged) {
        return;
    }

    // General settings
    saveCheckBox(mUi->checkEnableAdblock, AdBlock::AdBlockSettings::self()->adBlockEnabledItem());
    saveCheckBox(mUi->checkHideAds, AdBlock::AdBlockSettings::self()->hideAdsEnabledItem());
    saveSpinBox(mUi->spinBox, AdBlock::AdBlockSettings::self()->adBlockUpdateIntervalItem());
    // automatic filters
    KConfig config(QStringLiteral("AdBlockadblockrc"));
    const QStringList list = config.groupList().filter(QRegularExpression(QStringLiteral("FilterList \\d+")));
    foreach (const QString &group, list) {
        config.deleteGroup(group);
    }

    const int numberItem(mUi->automaticFiltersListWidget->count());
    for (int i = 0; i < numberItem; ++i) {
        QListWidgetItem *subItem = mUi->automaticFiltersListWidget->item(i);
        KConfigGroup grp = config.group(QStringLiteral("FilterList %1").arg(i));
        grp.writeEntry(QStringLiteral("FilterEnabled"), subItem->checkState() == Qt::Checked);
        grp.writeEntry(QStringLiteral("url"), subItem->data(UrlList).toString());
        grp.writeEntry(QStringLiteral("name"), subItem->text());
        if (subItem->data(LastUpdateList).toDateTime().isValid()) {
            grp.writeEntry(QStringLiteral("lastUpdate"), subItem->data(LastUpdateList).toDateTime());
        }
        QString path = subItem->data(PathList).toString();
        if (path.isEmpty()) {
            path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QLatin1Char('/') + QStringLiteral("kmail2/adblockrules-%1").arg(i);
        }
        grp.writeEntry(QStringLiteral("path"), path);
    }

    config.sync();
    // local filters
    const QString localRulesFilePath = AdBlock::AdBlockUtil::localFilterPath();

    QFile ruleFile(localRulesFilePath);
    if (!ruleFile.open(QFile::WriteOnly | QFile::Text)) {
        //FIXME qCDebug(AdBlock_LOG) << "Unable to open rule file" << localRulesFilePath;
        return;
    }

    QStringList disableCustomFilter;
    QTextStream out(&ruleFile);
    for (int i = 0; i < mUi->manualFiltersListWidget->count(); ++i) {
        QListWidgetItem *subItem = mUi->manualFiltersListWidget->item(i);
        const QString stringRule = subItem->text();
        if (!stringRule.trimmed().isEmpty()) {
            out << stringRule << '\n';
        }
        if (subItem->checkState() == Qt::Unchecked) {
            disableCustomFilter << stringRule;
        }
    }

    if (!disableCustomFilter.isEmpty()) {
        KConfigGroup grp = config.group(QStringLiteral("DisableRules"));
        grp.writeEntry("DisableRules", disableCustomFilter);
    } else {
        config.deleteGroup(QStringLiteral("DisableRules"));
    }
    // -------------------------------------------------------------------------------
    mChanged = false;
    Q_EMIT changed(false);
#ifdef AdBlock_USE_QTWEBENGINE
    //FIXME
#else
    //FIXME AdBlockManager::self()->reloadConfig();
#endif
}

void AdBlockSettingWidget::updateCheckBox()
{
    // update enabled status
    mUi->checkHideAds->setEnabled(mUi->checkEnableAdblock->isChecked());
    mUi->tabWidget->setEnabled(mUi->checkEnableAdblock->isChecked());
}

void AdBlockSettingWidget::hasChanged()
{
    updateCheckBox();
    mChanged = true;
    Q_EMIT changed(true);
    Q_EMIT settingsChanged();
}

bool AdBlockSettingWidget::changed() const
{
    return mChanged;
}

void AdBlockSettingWidget::slotAddFilter()
{
    QStringList excludeList;
    const int numberItem(mUi->automaticFiltersListWidget->count());
    excludeList.reserve(numberItem);
    for (int i = 0; i < numberItem; ++i) {
        excludeList << mUi->automaticFiltersListWidget->item(i)->text();
    }
    QPointer<AdBlock::AdBlockAddSubscriptionDialog> dlg = new AdBlock::AdBlockAddSubscriptionDialog(excludeList, this);
    if (dlg->exec()) {
        QString name;
        QString url;
        dlg->selectedList(name, url);
        QListWidgetItem *subItem = new QListWidgetItem(mUi->automaticFiltersListWidget);
        subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
        subItem->setCheckState(Qt::Checked);
        subItem->setText(name);
        subItem->setData(UrlList, url);
        subItem->setData(LastUpdateList, QDateTime());
        subItem->setData(PathList, QString());
        hasChanged();
    }
    delete dlg;
}

void AdBlockSettingWidget::slotRemoveSubscription()
{
    QListWidgetItem *item = mUi->automaticFiltersListWidget->currentItem();
    if (item) {
        if (KMessageBox::questionYesNo(this, i18n("Do you want to delete list \"%1\"?", item->text()), i18n("Delete current list")) == KMessageBox::Yes) {
            const QString path = item->data(PathList).toString();
            if (!path.isEmpty()) {
                if (!QFile(path).remove()) {
                    //FIXME qCDebug(AdBlock_LOG) << " we can not remove file:" << path;
                }
            }
            delete item;
        }
        hasChanged();
    }
}

void AdBlockSettingWidget::slotShowList()
{
    showAutomaticFilterList(mUi->automaticFiltersListWidget->currentItem());
}

void AdBlockSettingWidget::showAutomaticFilterList(QListWidgetItem *item)
{
    if (item) {
        QPointer<AdBlockShowListDialog> dlg = new AdBlockShowListDialog(true, this);
        dlg->setListName(item->text());
        dlg->setAdBlockListPath(item->data(PathList).toString(), item->data(UrlList).toString());
        connect(dlg.data(), &AdBlockShowListDialog::deleteList, this, &AdBlockSettingWidget::slotDeleteList);
        dlg->exec();
        delete dlg;
    }
}

void AdBlockSettingWidget::slotDeleteList(const QString &listName)
{
    QListWidgetItem *item = mUi->automaticFiltersListWidget->currentItem();
    if (item && item->text() == listName) {
        const QString path = item->data(PathList).toString();
        if (!path.isEmpty()) {
            if (!QFile(path).remove()) {
                //FIXME qCDebug(AdBlock_LOG) << " we can not remove file:" << path;
            }
        }
        delete item;
        hasChanged();
    }
}

void AdBlockSettingWidget::slotImportFilters()
{
    const QString filter = i18n("All Files (*)");
    const QString result = PimCommon::Util::loadToFile(filter, this, i18n("Import Filters"));
    if (result.isEmpty()) {
        return;
    }
    const QStringList listFilter = result.split(QLatin1Char('\n'));
    QStringList excludeFilter;
    const int numberOfElements(mUi->manualFiltersListWidget->count());
    excludeFilter.reserve(numberOfElements);
    for (int i = 0; i < numberOfElements; ++i) {
        QListWidgetItem *subItem = mUi->manualFiltersListWidget->item(i);
        excludeFilter.append(subItem->text());
    }

    Q_FOREACH (const QString &element, listFilter) {
        if (element == QLatin1String("\n")) {
            continue;
        }
        if (excludeFilter.contains(element)) {
            continue;
        }
        addManualFilter(element);
    }
}

void AdBlockSettingWidget::addManualFilter(const QString &text, const QStringList &excludeRules)
{
    QListWidgetItem *subItem = new QListWidgetItem(mUi->manualFiltersListWidget);
    subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    subItem->setCheckState(excludeRules.contains(text) ? Qt::Unchecked : Qt::Checked);
    subItem->setText(text);
}

void AdBlockSettingWidget::slotExportFilters()
{
    const QString filter = i18n("All Files (*)");
    QString exportFilters;
    const int numberOfElement(mUi->manualFiltersListWidget->count());
    for (int i = 0; i < numberOfElement; ++i) {
        QListWidgetItem *subItem = mUi->manualFiltersListWidget->item(i);
        const QString stringRule = subItem->text();
        if (!stringRule.isEmpty()) {
            exportFilters += stringRule + QLatin1Char('\n');
        }
    }
    PimCommon::Util::saveTextAs(exportFilters, filter, this, QUrl(), i18n("Export Filters"));
}

void AdBlockSettingWidget::slotAutomaticFilterDouble(QListWidgetItem *item)
{
    showAutomaticFilterList(item);
}

