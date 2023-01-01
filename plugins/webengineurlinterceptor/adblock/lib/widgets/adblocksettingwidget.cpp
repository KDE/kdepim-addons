/* ============================================================
 *
 * This file is a part of the rekonq project
 *
 * SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>
 * based on code from rekonq
 * SPDX-FileCopyrightText: 2010-2012 Andrea Diamantini <adjam7 at gmail dot com>
 *
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 *
 * ============================================================ */

// Self Includes
#include "adblocksettingwidget.h"
#include "adblockaddsubscriptiondialog.h"
#include "adblockinterceptor_debug.h"
#include "globalsettings_webengineurlinterceptoradblock.h"
#include "ui_settings_adblock.h"

#include "adblockmanager.h"
#include "adblockshowlistdialog.h"
#include "adblockutil.h"
#include <PimCommon/ConfigureImmutableWidgetUtils>
using namespace PimCommon::ConfigureImmutableWidgetUtils;

#include <PimCommon/PimUtil>

// KDE Includes
#include <KSharedConfig>

#include <QIcon>

#include <KLocalizedString>
#include <KMessageBox>
#include <QWhatsThisClickedEvent>

#include <KIO/JobUiDelegateFactory>
#include <KIO/OpenUrlJob>
#include <QPointer>
#include <QStandardPaths>
#include <QWhatsThis>
#include <adblocksubscription.h>

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

    mUi->manualFiltersListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    mUi->searchLine->setListWidget(mUi->manualFiltersListWidget);

    mUi->insertButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    connect(mUi->insertButton, &QToolButton::clicked, this, &AdBlockSettingWidget::insertRule);

    mUi->removeButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    connect(mUi->removeButton, &QPushButton::clicked, this, &AdBlockSettingWidget::removeRule);
    connect(mUi->removeSubscription, &QPushButton::clicked, this, &AdBlockSettingWidget::slotRemoveSubscription);
    connect(mUi->manualFiltersListWidget, &QListWidget::itemChanged, this, &AdBlockSettingWidget::slotManualFiltersChanged);
    connect(mUi->manualFiltersListWidget, &QListWidget::itemSelectionChanged, this, &AdBlockSettingWidget::slotSelectionChanged);
    mUi->spinBox->setSuffix(ki18np(" day", " days"));

    mUi->removeSubscription->setEnabled(false);
    mUi->showList->setEnabled(false);
    // Q_EMIT changed signal
    connect(mUi->checkEnableAdblock, &QCheckBox::stateChanged, this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->checkHideAds, &QCheckBox::stateChanged, this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->spinBox, qOverload<int>(&KPluralHandlingSpinBox::valueChanged), this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->addFilters, &QPushButton::clicked, this, &AdBlockSettingWidget::slotAddFilter);
    connect(mUi->showList, &QPushButton::clicked, this, &AdBlockSettingWidget::slotShowList);
    connect(mUi->editFilter, &QPushButton::clicked, this, &AdBlockSettingWidget::slotEditFilter);

    connect(mUi->automaticFiltersListWidget, &AdBlock::AdBlockListWidget::itemChanged, this, &AdBlockSettingWidget::hasChanged);
    connect(mUi->automaticFiltersListWidget, &AdBlock::AdBlockListWidget::currentItemChanged, this, &AdBlockSettingWidget::slotUpdateButtons);
    connect(mUi->automaticFiltersListWidget, &AdBlock::AdBlockListWidget::itemDoubleClicked, this, &AdBlockSettingWidget::slotAutomaticFilterDouble);

    connect(mUi->importFilters, &QPushButton::clicked, this, &AdBlockSettingWidget::slotImportFilters);
    connect(mUi->exportFilters, &QPushButton::clicked, this, &AdBlockSettingWidget::slotExportFilters);
    connect(mUi->addFilterLineEdit, &QLineEdit::textChanged, this, &AdBlockSettingWidget::slotManualFilterLineEditTextChanged);
    slotSelectionChanged();
    mUi->insertButton->setEnabled(false);
}

AdBlockSettingWidget::~AdBlockSettingWidget()
{
    delete mUi;
}

void AdBlockSettingWidget::slotManualFiltersChanged(QListWidgetItem *item)
{
    if (!mBlockUpdate) {
        const int offset = mUi->manualFiltersListWidget->row(item);
        if (offset >= 0) {
            const AdBlockRule *oldRule = mCustomSubscription->rule(mUi->manualFiltersListWidget->row(item));
            if (item->checkState() == Qt::Checked && !oldRule->isEnabled()) {
                const AdBlockRule *rule = mCustomSubscription->enableRule(offset);
            } else if (item->checkState() == Qt::Unchecked && oldRule->isEnabled()) {
                const AdBlockRule *rule = mCustomSubscription->disableRule(offset);
            } else if (mCustomSubscription->canEditRules()) {
                auto newRule = new AdBlockRule(item->text(), mCustomSubscription);
                const AdBlockRule *rule = mCustomSubscription->replaceRule(newRule, offset);
            }
            hasChanged();
        }
    }
}

void AdBlockSettingWidget::slotManualFilterLineEditTextChanged(const QString &text)
{
    mUi->insertButton->setEnabled(!text.trimmed().isEmpty());
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

void AdBlockSettingWidget::slotInfoLinkActivated(const QString &url)
{
    Q_UNUSED(url)

    const QString href = QStringLiteral("https://adblockplus.org/en/filters");
    const QString hintHelpString = i18n(
        "<qt><p>Enter an expression to filter. Filters can be defined as either:"
        "<ul><li>a shell-style wildcard, e.g. <tt>http://www.example.com/ads*</tt>, "
        "the wildcards <tt>*?[]</tt> may be used</li>"
        "<li>a full regular expression by surrounding the string with '<tt>/</tt>', "
        "e.g. <tt>/\\/(ad|banner)\\./</tt></li></ul>"
        "<p>Any filter string can be preceded by '<tt>@@</tt>' to whitelist (allow) any matching URL, "
        "which takes priority over any blacklist (blocking) filter.<br><a href=\'%1\'>%2</a></qt>",
        href,
        i18n("More information"));

    QWhatsThis::showText(QCursor::pos(), hintHelpString, this);
}

bool AdBlockSettingWidget::event(QEvent *event)
{
    if (event->type() == QEvent::WhatsThisClicked) {
        auto clicked = static_cast<QWhatsThisClickedEvent *>(event);
        auto job = new KIO::OpenUrlJob(QUrl(clicked->href()));
        job->setUiDelegate(KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, this));
        job->start();
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
    const QList<QListWidgetItem *> select = mUi->manualFiltersListWidget->selectedItems();
    if (select.isEmpty()) {
        return;
    }
    const int answer = KMessageBox::warningTwoActions(this,
                                                      i18np("Do you want to remove this rule?", "Do you want to remove these rules?", select.count()),
                                                      i18n("Remove"),
                                                      KStandardGuiItem::remove(),
                                                      KStandardGuiItem::cancel());
    if (answer == KMessageBox::ButtonCode::SecondaryAction) {
        return;
    }
    for (QListWidgetItem *item : select) {
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
    loadWidget(mUi->checkHideAds, AdBlock::AdBlockSettings::self()->hideAdsEnabledItem());
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
    for (AdBlockSubscription *subscription : AdblockManager::self()->subscriptions()) {
        const QString url = subscription->url().toString();
        const QString name = subscription->title();
        if (!url.isEmpty()) {
            auto subItem = new AdBlockListwidgetItem(mUi->automaticFiltersListWidget);
            subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
            subItem->setSubscription(subscription);
            if (subscription->enabled()) {
                subItem->setCheckState(Qt::Checked);
            } else {
                subItem->setCheckState(Qt::Unchecked);
            }

            subItem->setData(UrlList, url);
            subItem->setText(name);
        } else { // Custom .
            mCustomSubscription = subscription;
            mBlockUpdate = true;
            for (AdBlockRule *rule : subscription->allRules()) {
                auto subItem = new QListWidgetItem(mUi->manualFiltersListWidget);
                subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEditable);
                subItem->setCheckState(rule->isEnabled() ? Qt::Checked : Qt::Unchecked);
                subItem->setText(rule->filter());
            }
            mBlockUpdate = false;
        }
    }

    // ------------------------------------------------------------------------------
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

    if (mCustomSubscription) {
        mCustomSubscription->saveSubscription();
    }
    mChanged = false;
    Q_EMIT changed(false);
    AdBlock::AdBlockSettings::self()->save();
    AdBlock::AdblockManager::self()->save();
    AdBlock::AdblockManager::self()->reloadConfig();
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
        if (AdBlockSubscription *subscription = AdblockManager::self()->addSubscription(name, url)) {
            auto subItem = new AdBlockListwidgetItem(mUi->automaticFiltersListWidget);
            subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
            subItem->setCheckState(Qt::Checked);
            subItem->setText(name);
            subItem->setData(UrlList, url);
            subItem->setData(PathList, QString());
            subItem->setSubscription(subscription);
            hasChanged();
        }
    }
    delete dlg;
}

void AdBlockSettingWidget::slotRemoveSubscription()
{
    QListWidgetItem *item = mUi->automaticFiltersListWidget->currentItem();
    if (item) {
        const int answer = KMessageBox::questionTwoActions(this,
                                                           i18n("Do you want to delete list \"%1\"?", item->text()),
                                                           i18n("Delete current list"),
                                                           KStandardGuiItem::del(),
                                                           KStandardGuiItem::cancel());
        if (answer == KMessageBox::ButtonCode::PrimaryAction) {
            auto subItem = dynamic_cast<AdBlockListwidgetItem *>(item);
            if (subItem) {
                if (AdblockManager::self()->removeSubscription(subItem->subscription())) {
                    hasChanged();
                    delete subItem;
                }
            }
        }
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
    auto item = dynamic_cast<AdBlockListwidgetItem *>(mUi->automaticFiltersListWidget->currentItem());
    if (item && item->text() == listName) {
        if (AdblockManager::self()->removeSubscription(item->subscription())) {
            delete item;
            hasChanged();
        }
    }
}

void AdBlockSettingWidget::slotImportFilters()
{
    const QString filter = i18n("All Files (*)");
    const QString result = PimCommon::Util::loadToFile(filter, this, QUrl(), i18n("Import Filters"));
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

    for (const QString &element : listFilter) {
        if (element == QLatin1Char('\n')) {
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
    auto rule = new AdBlockRule(text, mCustomSubscription);
    if (excludeRules.contains(text)) {
        rule->setEnabled(false);
    }
    const int offset = mCustomSubscription->addRule(rule);
    if (offset >= 0) {
        auto subItem = new QListWidgetItem(mUi->manualFiltersListWidget);
        subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEditable);
        subItem->setCheckState(excludeRules.contains(text) ? Qt::Unchecked : Qt::Checked);
        subItem->setText(text);
    }
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

void AdBlockSettingWidget::slotSelectionChanged()
{
    const int numberOfElement(mUi->manualFiltersListWidget->selectedItems().count());
    mUi->exportFilters->setEnabled(numberOfElement > 0);
    mUi->editFilter->setEnabled(numberOfElement == 1);
    mUi->removeButton->setEnabled(numberOfElement > 0);
}

AdBlockListwidgetItem::AdBlockListwidgetItem(QListWidget *parent)
    : QListWidgetItem(parent)
{
}

AdBlockSubscription *AdBlockListwidgetItem::subscription() const
{
    return mSubscription;
}

void AdBlockListwidgetItem::setSubscription(AdBlockSubscription *subscription)
{
    mSubscription = subscription;
}
