/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockautomaticruleslistwidget.h"

using namespace AdBlock;

AdBlockAutomaticRulesListWidget::AdBlockAutomaticRulesListWidget(QWidget *parent)
    : QListWidget(parent)
{
    connect(this, &AdBlockAutomaticRulesListWidget::itemChanged, this, &AdBlockAutomaticRulesListWidget::slotItemChanged);
}

AdBlockAutomaticRulesListWidget::~AdBlockAutomaticRulesListWidget() = default;

void AdBlockAutomaticRulesListWidget::slotItemChanged(QListWidgetItem *item)
{
    updateItem(item);
}

void AdBlockAutomaticRulesListWidget::updateItem(QListWidgetItem *item)
{
    const bool itemIsChecked = (item->checkState() & Qt::Checked);
    QFont font = item->font();
    const QString rule = item->text();
    if (itemIsChecked) {
        font.setItalic(false);
        item->setFont(font);
        if (rule.contains(QRegularExpression(QStringLiteral("^@@.*")))) {
            item->setForeground(Qt::magenta);
        } else if (rule.contains(QRegularExpression(QStringLiteral("^\\[.*")))) {
            item->setForeground(Qt::red);
        } else if (rule.contains(QRegularExpression(QStringLiteral(".*##.*")))) {
            item->setForeground(Qt::blue);
        } else {
            if (!defaultTextColor.isValid()) {
                const QPalette palette = viewport()->palette();
                defaultTextColor = palette.text().color();
            }
            item->setForeground(defaultTextColor);
        }
    } else {
        font.setItalic(true);
        item->setFont(font);
        item->setForeground(Qt::gray);
    }
}

void AdBlockAutomaticRulesListWidget::setDisabledRules(const QStringList &disabledRules)
{
    mDisabledRules = disabledRules;
}

void AdBlockAutomaticRulesListWidget::setRules(const QString &rules)
{
    clear();
    const QStringList lst = rules.split(QLatin1Char('\n'), Qt::SkipEmptyParts);
    for (const QString &rule : lst) {
        createItem(rule);
    }
}

void AdBlockAutomaticRulesListWidget::createItem(const QString &rule)
{
    auto subItem = new QListWidgetItem(this);
    subItem->setText(rule);
    if (rule.startsWith(QLatin1Char('!')) || rule.startsWith(QLatin1Char('['))) {
        // Comment
        subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
        subItem->setForeground(Qt::gray);
    } else {
        subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
        const bool checkState = mDisabledRules.contains(rule);
        subItem->setCheckState(checkState ? Qt::Unchecked : Qt::Checked);
        updateItem(subItem);
    }
}

QStringList AdBlockAutomaticRulesListWidget::disabledRules() const
{
    QStringList currentDisabledRules;
    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *row = item(i);
        if (row->flags() & Qt::ItemIsUserCheckable) {
            if (row->checkState() == Qt::Unchecked) {
                currentDisabledRules << row->text();
            }
        }
    }
    return currentDisabledRules;
}
