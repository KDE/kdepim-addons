/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "kmailconfirmbeforedeleting_export.h"
#include <Akonadi/Item>
#include <KConfigGroup>
#include <KMime/Message>
#include <QString>
class QDebug;
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
        Bcc,
        Unread,
        Important,
    };
    Q_ENUM(RuleType)

    ConfirmBeforeDeletingRule();
    ~ConfirmBeforeDeletingRule();

    [[nodiscard]] const QString &pattern() const;
    void setPattern(const QString &newPattern);

    [[nodiscard]] RuleType ruleType() const;
    void setRuleType(RuleType newRuleType);

    [[nodiscard]] bool deletingNeedToConfirm(const Akonadi::Item &item, QString &checkFoundInfo) const;

    void save(KConfigGroup &group) const;
    void load(const KConfigGroup &group);

    [[nodiscard]] bool isValid() const;
    [[nodiscard]] static QString ruleTypeToString(ConfirmBeforeDeletingRule::RuleType r);
    [[nodiscard]] static ConfirmBeforeDeletingRule::RuleType stringToRuleType(const QString &str);

    [[nodiscard]] bool operator==(const ConfirmBeforeDeletingRule &other) const;

private:
    KMAILCONFIRMBEFOREDELETING_NO_EXPORT void generateConfirmMessageInfo(const std::shared_ptr<KMime::Message> &msg, QString &checkFoundInfo) const;
    KMAILCONFIRMBEFOREDELETING_NO_EXPORT void
    generateConfirmMessageInfoFromStatus(const std::shared_ptr<KMime::Message> &msg, QString &checkFoundInfo, const QString &statusStr) const;
    QString mPattern;
    RuleType mRuleType = RuleType::Unknown;
};
Q_DECLARE_TYPEINFO(ConfirmBeforeDeletingRule, Q_RELOCATABLE_TYPE);
KMAILCONFIRMBEFOREDELETING_EXPORT QDebug operator<<(QDebug d, const ConfirmBeforeDeletingRule &t);
