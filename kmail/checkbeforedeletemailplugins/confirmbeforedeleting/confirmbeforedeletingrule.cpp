/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingrule.h"
#include "confirmbeforedeletingplugin_debug.h"

ConfirmBeforeDeletingRule::ConfirmBeforeDeletingRule()
{
}

ConfirmBeforeDeletingRule::~ConfirmBeforeDeletingRule()
{
}

const QString &ConfirmBeforeDeletingRule::pattern() const
{
    return mPattern;
}

void ConfirmBeforeDeletingRule::setPattern(const QString &newPattern)
{
    mPattern = newPattern;
}

ConfirmBeforeDeletingRule::RuleType ConfirmBeforeDeletingRule::ruleType() const
{
    return mRuleType;
}

void ConfirmBeforeDeletingRule::setRuleType(RuleType newRuleType)
{
    mRuleType = newRuleType;
}

bool ConfirmBeforeDeletingRule::deletingNeedToConfirm(const Akonadi::Item &item) const
{
    switch (mRuleType) {
    case Body:
        break;
    case Subject:
        break;
    case To:
        break;
    case Cc:
        break;
    case Unknown:
        qCWarning(KMAIL_CONFIRMBEFOREDELETING_PLUGIN_LOG) << "Invalid rules!";
        break;
    }
    return false;
}

QDebug operator<<(QDebug d, const ConfirmBeforeDeletingRule &t)
{
    d << "Pattern " << t.pattern();
    d << "mRuleType " << t.ruleType();
    return d;
}
