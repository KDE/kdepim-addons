/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingrule.h"
#include "confirmbeforedeletingplugin_debug.h"

#include <KLocalizedString>

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

void ConfirmBeforeDeletingRule::load(const KConfigGroup &group)
{
    const QString pattern = group.readEntry(QStringLiteral("Pattern"), QString());
    const QString checkType = group.readEntry(QStringLiteral("Type"), QString());
    setPattern(pattern);
    setRuleType(stringToRuleType(checkType));
}

bool ConfirmBeforeDeletingRule::isValid() const
{
    return !mPattern.isEmpty() && (mRuleType != Unknown);
}

void ConfirmBeforeDeletingRule::save(KConfigGroup &group) const
{
    group.writeEntry(QStringLiteral("Pattern"), mPattern);
    group.writeEntry(QStringLiteral("Type"), ruleTypeToString(mRuleType));
}

ConfirmBeforeDeletingRule::RuleType ConfirmBeforeDeletingRule::stringToRuleType(const QString &str)
{
    if (str == QLatin1String("body")) {
        return Body;
    } else if (str == QLatin1String("subject")) {
        return Subject;
    } else if (str == QLatin1String("to")) {
        return To;
    } else if (str == QLatin1String("cc")) {
        return Cc;
    } else if (str == QLatin1String("bcc")) {
        return Bcc;
    }
    return Unknown;
}

bool ConfirmBeforeDeletingRule::operator==(const ConfirmBeforeDeletingRule &other) const
{
    return mPattern == other.pattern() && mRuleType == other.ruleType();
}

QString ConfirmBeforeDeletingRule::ruleTypeToString(ConfirmBeforeDeletingRule::RuleType r)
{
    QString tmp;
    switch (r) {
    case Unknown:
        break;
    case Body:
        tmp = QStringLiteral("body");
        break;
    case Subject:
        tmp = QStringLiteral("subject");
        break;
    case To:
        tmp = QStringLiteral("to");
        break;
    case Cc:
        tmp = QStringLiteral("cc");
        break;
    case Bcc:
        tmp = QStringLiteral("bcc");
        break;
    }
    return tmp;
}

bool ConfirmBeforeDeletingRule::deletingNeedToConfirm(const Akonadi::Item &item, QString &checkFoundInfo) const
{
    bool needToConfirm = false;
    if (item.hasPayload<KMime::Message::Ptr>()) {
        auto msg = item.payload<KMime::Message::Ptr>();
        switch (mRuleType) {
        case Body: {
            const auto ba = msg->body();
            if (QString::fromUtf8(ba).contains(pattern())) {
                needToConfirm = true;
                generateConfirmMessageInfo(msg, checkFoundInfo);
            }
            break;
        }
        case Subject: {
            if (auto subject = msg->subject(false)) {
                const QString subjectStr = subject->asUnicodeString();
                if (subjectStr.contains(pattern())) {
                    needToConfirm = true;
                    generateConfirmMessageInfo(msg, checkFoundInfo);
                }
            }
            break;
        }
        case To: {
            if (auto to = msg->to(false)) {
                const QString toStr = to->asUnicodeString();
                if (toStr.contains(pattern())) {
                    needToConfirm = true;
                    generateConfirmMessageInfo(msg, checkFoundInfo);
                }
            }
            break;
        }
        case Cc: {
            if (auto cc = msg->cc(false)) {
                const QString ccStr = cc->asUnicodeString();
                if (ccStr.contains(pattern())) {
                    needToConfirm = true;
                    generateConfirmMessageInfo(msg, checkFoundInfo);
                }
            }
            break;
        }
        case Bcc: {
            if (auto bcc = msg->bcc(false)) {
                const QString bccStr = bcc->asUnicodeString();
                if (bccStr.contains(pattern())) {
                    needToConfirm = true;
                    generateConfirmMessageInfo(msg, checkFoundInfo);
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

void ConfirmBeforeDeletingRule::generateConfirmMessageInfo(const KMime::Message::Ptr &msg, QString &checkFoundInfo) const
{
    QString subjectStr;
    if (auto subject = msg->subject(false)) {
        subjectStr = subject->asUnicodeString();
    }
    checkFoundInfo = i18n("The message with subject \'%2\' contains \'%1\'", pattern(), subjectStr);
}

QDebug operator<<(QDebug d, const ConfirmBeforeDeletingRule &t)
{
    d << "Pattern " << t.pattern();
    d << "mRuleType " << t.ruleType();
    return d;
}
