/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "adblockautomaticruleslistwidget.h"

using namespace AdBlock;

AdBlockAutomaticRulesListWidget::AdBlockAutomaticRulesListWidget(QWidget *parent)
    : QListWidget(parent)
{
    connect(this, &AdBlockAutomaticRulesListWidget::itemChanged, this, &AdBlockAutomaticRulesListWidget::slotItemChanged);
}

AdBlockAutomaticRulesListWidget::~AdBlockAutomaticRulesListWidget()
{

}

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
            item->setTextColor(Qt::magenta);
        } else if (rule.contains(QRegularExpression(QStringLiteral("^\\[.*")))) {
            item->setTextColor(Qt::red);
        } else if (rule.contains(QRegularExpression(QStringLiteral(".*##.*")))) {
            item->setTextColor(Qt::blue);
        } else {
            if (!defaultTextColor.isValid()) {
                const QPalette palette = viewport()->palette();
                defaultTextColor = palette.text().color();
            }
            item->setTextColor(defaultTextColor);
        }
    } else {
        font.setItalic(true);
        item->setFont(font);
        item->setTextColor(Qt::gray);
    }
}

void AdBlockAutomaticRulesListWidget::setDisabledRules(const QStringList &disabledRules)
{
    mDisabledRules = disabledRules;
}

void AdBlockAutomaticRulesListWidget::setRules(const QString &rules)
{
    clear();
    const QStringList lst = rules.split(QLatin1Char('\n'), QString::SkipEmptyParts);
    for (const QString &rule : lst) {
        createItem(rule);
    }
}

void AdBlockAutomaticRulesListWidget::createItem(const QString &rule)
{
    QListWidgetItem *subItem = new QListWidgetItem(this);
    subItem->setText(rule);
    if (rule.startsWith(QLatin1Char('!')) || rule.startsWith(QLatin1Char('['))) {
        //Comment
        subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
        subItem->setTextColor(Qt::gray);
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

