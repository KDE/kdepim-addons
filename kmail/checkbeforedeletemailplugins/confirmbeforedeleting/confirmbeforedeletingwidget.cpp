/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidget.h"
#include "confirmbeforedeletingcreateruledialog.h"
#include "confirmbeforedeletingmanager.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QIcon>
#include <QMenu>
#include <QPointer>
#include <QTreeWidget>
#include <QVBoxLayout>

ConfirmBeforeDeletingWidget::ConfirmBeforeDeletingWidget(QWidget *parent)
    : QWidget(parent)
    , mTreeWidget(new QTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mTreeWidget->setObjectName(QStringLiteral("mTreeWidget"));
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setAlternatingRowColors(true);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mTreeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    const QStringList lst = {i18n("Type"), i18n("Pattern")};
    mTreeWidget->setHeaderLabels(lst);
    connect(mTreeWidget, &QTreeWidget::customContextMenuRequested, this, &ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested);
    connect(mTreeWidget, &QTreeWidget::itemDoubleClicked, this, &ConfirmBeforeDeletingWidget::slotEditRule);
    fillRules();
}

ConfirmBeforeDeletingWidget::~ConfirmBeforeDeletingWidget()
{
}

void ConfirmBeforeDeletingWidget::fillRules()
{
    const QVector<ConfirmBeforeDeletingRule> rules = ConfirmBeforeDeletingManager::self()->rules();
    for (const ConfirmBeforeDeletingRule &r : rules) {
        auto item = new QTreeWidgetItem(mTreeWidget);
        ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info;
        info.pattern = r.pattern();
        info.ruleType = ConfirmBeforeDeletingRule::ruleTypeToString(r.ruleType());
        initializeItem(item, info);
    }
}

void ConfirmBeforeDeletingWidget::slotEditRule()
{
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (item) {
        QPointer<ConfirmBeforeDeletingCreateRuleDialog> dlg = new ConfirmBeforeDeletingCreateRuleDialog(this);
        ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo currentInfo;
        currentInfo.pattern = item->text(1);
        currentInfo.ruleType = item->text(0);
        dlg->setInfo(currentInfo);
        if (dlg->exec()) {
            initializeItem(item, dlg->info());
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
    const int selectedItemCount{mTreeWidget->selectedItems().count()};
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
        if (KMessageBox::questionYesNo(this,
                                       i18np("Do you want to remove this rule?", "Do you want to remove these rules?", items.count()),
                                       i18nc("@title", "Remove Rule"))
            == KMessageBox::Yes) {
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
        auto item = new QTreeWidgetItem(mTreeWidget);
        initializeItem(item, dlg->info());
    }
    delete dlg;
}

void ConfirmBeforeDeletingWidget::save()
{
    QVector<ConfirmBeforeDeletingRule> rules;
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
