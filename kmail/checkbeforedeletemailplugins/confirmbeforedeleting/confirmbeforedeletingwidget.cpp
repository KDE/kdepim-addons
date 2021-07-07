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
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setAlternatingRowColors(true);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    const QStringList lst = {i18n("Pattern"), i18n("Type")};
    mTreeWidget->setHeaderLabels(lst);
    connect(mTreeWidget, &QTreeWidget::customContextMenuRequested, this, &ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested);
    fillRules();
}

ConfirmBeforeDeletingWidget::~ConfirmBeforeDeletingWidget()
{
}

void ConfirmBeforeDeletingWidget::fillRules()
{
    const QVector<ConfirmBeforeDeletingRule> rules = ConfirmBeforeDeletingManager::self()->rules();
    for (const ConfirmBeforeDeletingRule &r : rules) {
        auto item = new QTreeWidgetItem(mTreeWidget, {ConfirmBeforeDeletingRule::ruleTypeToString(r.ruleType()), r.pattern()});
        item->setText(0, r.pattern());
        item->setText(1, ConfirmBeforeDeletingRule::ruleTypeToString(r.ruleType()));
    }
}

void ConfirmBeforeDeletingWidget::slotEditRule()
{
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    QPointer<ConfirmBeforeDeletingCreateRuleDialog> dlg = new ConfirmBeforeDeletingCreateRuleDialog(this);
    ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo currentInfo;
    currentInfo.pattern = item->text(0);
    currentInfo.ruleType = item->text(1);
    dlg->setInfo(currentInfo);
    if (dlg->exec()) {
        const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info = dlg->info();
        item->setText(0, info.pattern);
        item->setText(1, info.ruleType);
    }
    delete dlg;
}

void ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested(const QPoint &p)
{
    QMenu menu(this);
    menu.addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Add Rule..."), this, &ConfirmBeforeDeletingWidget::slotAddRule);
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (item) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Edit Rule..."), this, &ConfirmBeforeDeletingWidget::slotEditRule);
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove Rule"), this, &ConfirmBeforeDeletingWidget::slotRemoveRule);
    }
    menu.exec(QCursor::pos());
}

void ConfirmBeforeDeletingWidget::slotRemoveRule()
{
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (item) {
        if (KMessageBox::questionYesNo(this, i18n("Do you want to remove this rule?"), i18n("Remove Rule")) == KMessageBox::Yes) {
            delete item;
        }
    }
}

void ConfirmBeforeDeletingWidget::slotAddRule()
{
    QPointer<ConfirmBeforeDeletingCreateRuleDialog> dlg = new ConfirmBeforeDeletingCreateRuleDialog(this);
    if (dlg->exec()) {
        const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo info = dlg->info();
        auto item = new QTreeWidgetItem(mTreeWidget);
        item->setText(0, info.pattern);
        item->setText(1, info.ruleType);
    }
    delete dlg;
}

void ConfirmBeforeDeletingWidget::save()
{
    QVector<ConfirmBeforeDeletingRule> rules;
    for (int i = 0, total = mTreeWidget->topLevelItemCount(); i < total; ++i) {
        QTreeWidgetItem *item = mTreeWidget->topLevelItem(i);
        ConfirmBeforeDeletingRule r;
        r.setPattern(item->text(0));
        r.setRuleType(ConfirmBeforeDeletingRule::stringToRuleType(item->text(1)));
        rules.append(r);
    }
    ConfirmBeforeDeletingManager::self()->setRules(rules);
    ConfirmBeforeDeletingManager::self()->saveRules();
}
