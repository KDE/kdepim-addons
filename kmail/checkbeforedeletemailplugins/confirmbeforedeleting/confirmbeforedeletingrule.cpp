/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingrule.h"
#include "confirmbeforedeletingplugin_debug.h"
#include <KMime/Message>
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
    bool needToConfirm = false;
    if (item.hasPayload<KMime::Message::Ptr>()) {
        auto msg = item.payload<KMime::Message::Ptr>();
        switch (mRuleType) {
        case Body: {
            const auto ba = msg->body();
            if (QString::fromUtf8(ba).contains(pattern())) {
                needToConfirm = true;
            }
            break;
        }
        case Subject: {
            if (auto subject = msg->subject(false)) {
                const QString subjectStr = subject->asUnicodeString();
                if (subjectStr.contains(pattern())) {
                    needToConfirm = true;
                }
            }
            break;
        }
        case To: {
            if (auto to = msg->to(false)) {
                const QString toStr = to->asUnicodeString();
                if (toStr.contains(pattern())) {
                    needToConfirm = true;
                }
            }
            break;
        }
        case Cc: {
            if (auto cc = msg->cc(false)) {
                const QString ccStr = cc->asUnicodeString();
                if (ccStr.contains(pattern())) {
                    needToConfirm = true;
                }
            }
            break;
        }
        case Unknown:
            qCWarning(KMAIL_CONFIRMBEFOREDELETING_PLUGIN_LOG) << "Invalid rules!";
            break;
        }
    }

    return needToConfirm;
}

QDebug operator<<(QDebug d, const ConfirmBeforeDeletingRule &t)
{
    d << "Pattern " << t.pattern();
    d << "mRuleType " << t.ruleType();
    return d;
}
