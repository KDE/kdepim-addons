/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidget.h"
#include "confirmbeforedeletingcreateruledialog.h"
#include "confirmbeforedeletingmanager.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QHeaderView>
#include <QIcon>
#include <QMenu>
#include <QPointer>
#include <QPushButton>
#include <QTreeWidget>
#include <QVBoxLayout>

ConfirmBeforeDeletingWidget::ConfirmBeforeDeletingWidget(QWidget *parent)
    : QWidget(parent)
    , mTreeWidget(new QTreeWidget(this))
    , mAddRule(new QPushButton(i18nc("@action:button", "Add Rule..."), this))
    , mRemoveRule(new QPushButton(i18nc("@action:button", "Remove Rule"), this))
    , mModifyRule(new QPushButton(i18nc("@action:button", "Modify Rule..."), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    auto listLayout = new QHBoxLayout;
    mainLayout->addLayout(listLayout);

    mTreeWidget->setObjectName(QLatin1StringView("mTreeWidget"));
    listLayout->addWidget(mTreeWidget);
    mTreeWidget->setAlternatingRowColors(true);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mTreeWidget->header()->setSortIndicatorShown(true);
    mTreeWidget->setSortingEnabled(true);
    const QStringList lst = {i18n("Type"), i18n("Pattern")};
    mTreeWidget->setHeaderLabels(lst);
    connect(mTreeWidget, &QTreeWidget::customContextMenuRequested, this, &ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested);
    connect(mTreeWidget, &QTreeWidget::itemDoubleClicked, this, &ConfirmBeforeDeletingWidget::slotEditRule);
    connect(mTreeWidget, &QTreeWidget::itemSelectionChanged, this, &ConfirmBeforeDeletingWidget::updateButtons);

    auto buttonLayout = new QVBoxLayout;
    listLayout->addLayout(buttonLayout);

    connect(mAddRule, &QPushButton::clicked, this, &ConfirmBeforeDeletingWidget::slotAddRule);
    mAddRule->setObjectName(QLatin1StringView("mAddRule"));
    buttonLayout->addWidget(mAddRule);

    connect(mModifyRule, &QPushButton::clicked, this, &ConfirmBeforeDeletingWidget::slotEditRule);
    mModifyRule->setObjectName(QLatin1StringView("mModifyRule"));
    buttonLayout->addWidget(mModifyRule);

    connect(mRemoveRule, &QPushButton::clicked, this, &ConfirmBeforeDeletingWidget::slotRemoveRule);
    mRemoveRule->setObjectName(QLatin1StringView("mRemoveRule"));
    buttonLayout->addWidget(mRemoveRule);
    buttonLayout->addStretch(1);
    updateButtons();

    fillRules();
}

ConfirmBeforeDeletingWidget::~ConfirmBeforeDeletingWidget() = default;

void ConfirmBeforeDeletingWidget::updateButtons()
{
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (item) {
        mRemoveRule->setEnabled(true);
        mModifyRule->setEnabled(true);
    } else {
        mRemoveRule->setEnabled(false);
        mModifyRule->setEnabled(false);
    }
}

void ConfirmBeforeDeletingWidget::fillRules()
{
    const QList<ConfirmBeforeDeletingRule> rules = ConfirmBeforeDeletingManager::self()->rules();
    for (const ConfirmBeforeDeletingRule &r : rules) {
        auto item = new QTreeWidgetItem(mTreeWidget);
        const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info(r.pattern(), ConfirmBeforeDeletingRule::ruleTypeToString(r.ruleType()));
        initializeItem(item, info);
    }
}

void ConfirmBeforeDeletingWidget::slotEditRule()
{
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (item) {
        QPointer<ConfirmBeforeDeletingCreateRuleDialog> dlg = new ConfirmBeforeDeletingCreateRuleDialog(this);
        const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo currentInfo(item->text(1), item->text(0));
        dlg->setInfo(currentInfo);
        if (dlg->exec()) {
            const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo newInfo = dlg->info();
            if (currentInfo != newInfo) {
                initializeItem(item, newInfo);
            }
        }
        delete dlg;
    }
}

void ConfirmBeforeDeletingWidget::initializeItem(QTreeWidgetItem *item, const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info)
{
    item->setText(1, info.pattern);
    item->setText(0, info.ruleType);
}

void ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested(const QPoint &p)
{
    QMenu menu(this);
    const auto selectedItemCount{mTreeWidget->selectedItems().count()};
    menu.addAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add Rule..."), this, &ConfirmBeforeDeletingWidget::slotAddRule);
    if (selectedItemCount == 1) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18n("Edit Rule..."), this, &ConfirmBeforeDeletingWidget::slotEditRule);
    }
    if (selectedItemCount > 0) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("list-remove")),
                       i18np("Remove Rule", "Remove Rules", selectedItemCount),
                       this,
                       &ConfirmBeforeDeletingWidget::slotRemoveRule);
    }
    menu.exec(QCursor::pos());
}

void ConfirmBeforeDeletingWidget::slotRemoveRule()
{
    auto items = mTreeWidget->selectedItems();
    if (!items.isEmpty()) {
        const int answer = KMessageBox::questionTwoActions(this,
                                                           i18np("Do you want to remove this rule?", "Do you want to remove these rules?", items.count()),
                                                           i18nc("@title", "Remove Rule"),
                                                           KStandardGuiItem::remove(),
                                                           KStandardGuiItem::cancel());

        if (answer == KMessageBox::ButtonCode::PrimaryAction) {
            while (!items.isEmpty()) {
                delete items.takeFirst();
            }
        }
    }
}

void ConfirmBeforeDeletingWidget::slotAddRule()
{
    QPointer<ConfirmBeforeDeletingCreateRuleDialog> dlg = new ConfirmBeforeDeletingCreateRuleDialog(this);
    if (dlg->exec()) {
        const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info = dlg->info();
        ConfirmBeforeDeletingRule r;
        r.setPattern(info.pattern);
        r.setRuleType(ConfirmBeforeDeletingRule::stringToRuleType(info.ruleType));

        bool ruleFound = false;
        for (int i = 0, total = mTreeWidget->topLevelItemCount(); i < total; ++i) {
            QTreeWidgetItem *item = mTreeWidget->topLevelItem(i);
            ConfirmBeforeDeletingRule currentRule;
            currentRule.setPattern(item->text(1));
            currentRule.setRuleType(ConfirmBeforeDeletingRule::stringToRuleType(item->text(0)));
            if (currentRule == r) {
                KMessageBox::information(this, i18n("Same rule already exists."), i18n("Create Rule"));
                ruleFound = true;
                break;
            }
        }
        if (!ruleFound) {
            auto item = new QTreeWidgetItem(mTreeWidget);
            initializeItem(item, dlg->info());
        }
    }
    delete dlg;
}

void ConfirmBeforeDeletingWidget::save()
{
    QList<ConfirmBeforeDeletingRule> rules;
    for (int i = 0, total = mTreeWidget->topLevelItemCount(); i < total; ++i) {
        QTreeWidgetItem *item = mTreeWidget->topLevelItem(i);
        ConfirmBeforeDeletingRule r;
        r.setPattern(item->text(1));
        r.setRuleType(ConfirmBeforeDeletingRule::stringToRuleType(item->text(0)));
        rules.append(r);
    }
    ConfirmBeforeDeletingManager::self()->setRules(rules);
    ConfirmBeforeDeletingManager::self()->saveRules();
}

#include "moc_confirmbeforedeletingwidget.cpp"
