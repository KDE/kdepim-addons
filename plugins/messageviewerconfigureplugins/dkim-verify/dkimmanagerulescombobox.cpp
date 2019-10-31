/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimmanagerulescombobox.h"
#include <KLocalizedString>

DKIMManageRulesComboBox::DKIMManageRulesComboBox(QWidget *parent)
    : QComboBox(parent)
{
    init();
}

DKIMManageRulesComboBox::~DKIMManageRulesComboBox()
{

}

void DKIMManageRulesComboBox::init()
{
    addItem(i18n("Must be signed"), QVariant::fromValue(MessageViewer::DKIMRule::RuleType::MustBeSigned));
    addItem(i18n("Can be signed"), QVariant::fromValue(MessageViewer::DKIMRule::RuleType::CanBeSigned));
    addItem(i18n("Ignore if not signed"), QVariant::fromValue(MessageViewer::DKIMRule::RuleType::IgnoreEmailNotSigned));
}

MessageViewer::DKIMRule::RuleType DKIMManageRulesComboBox::ruleType() const
{
    return currentData().value<MessageViewer::DKIMRule::RuleType>();
}

void DKIMManageRulesComboBox::setRuleType(MessageViewer::DKIMRule::RuleType type)
{
    const int index = findData(QVariant::fromValue(type));
    if (index != -1) {
        setCurrentIndex(index);
    }
}
