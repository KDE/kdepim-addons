﻿/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "kmailconfirmbeforedeleting_export.h"
#include <AkonadiCore/Item>
#include <KConfigGroup>
#include <KMime/Message>
#include <QDebug>
#include <QString>
class KMAILCONFIRMBEFOREDELETING_EXPORT ConfirmBeforeDeletingRule
{
    Q_GADGET
public:
    enum RuleType {
        Unknown = 0,
        Body,
        Subject,
        To,
        Cc,
    };
    Q_ENUM(RuleType)

    ConfirmBeforeDeletingRule();
    ~ConfirmBeforeDeletingRule();

    Q_REQUIRED_RESULT const QString &pattern() const;
    void setPattern(const QString &newPattern);

    Q_REQUIRED_RESULT RuleType ruleType() const;
    void setRuleType(RuleType newRuleType);

    Q_REQUIRED_RESULT bool deletingNeedToConfirm(const Akonadi::Item &item, QString &checkFoundInfo) const;

    void save(KConfigGroup &group) const;
    void load(const KConfigGroup &group);

    Q_REQUIRED_RESULT bool isValid() const;
    static Q_REQUIRED_RESULT QString ruleTypeToString(ConfirmBeforeDeletingRule::RuleType r);
    static Q_REQUIRED_RESULT ConfirmBeforeDeletingRule::RuleType stringToRuleType(const QString &str);

private:
    void generateConfirmMessageInfo(const KMime::Message::Ptr &msg, QString &checkFoundInfo) const;
    QString mPattern;
    RuleType mRuleType = RuleType::Unknown;
};
Q_DECLARE_TYPEINFO(ConfirmBeforeDeletingRule, Q_MOVABLE_TYPE);
KMAILCONFIRMBEFOREDELETING_EXPORT QDebug operator<<(QDebug d, const ConfirmBeforeDeletingRule &t);
