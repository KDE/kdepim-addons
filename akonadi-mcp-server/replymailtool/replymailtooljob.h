/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/kmaildbustooljobbase.h"

class ReplyMailToolJob : public KMailDBusToolJobBase
{
    Q_OBJECT
public:
    // Same values as MessageComposer::ReplyStrategy, sent as is to KMail
    enum class ReplyStrategy : uint8_t {
        ReplySmart = 0, //< Attempt to automatically guess the best recipient for the reply
        ReplyAuthor, //< Reply to the author of the message (possibly NOT the mailing list, if any)
        ReplyList, //< Reply to the mailing list (and not the author of the message)
        ReplyAll, //< Reply to author and all the recipients in CC
        ReplyNone, //< Don't set reply addresses: they will be set manually
    };

    explicit ReplyMailToolJob(QObject *parent = nullptr);
    ~ReplyMailToolJob() override;

    void setItemId(qint64 id);
    void setReplyStrategy(ReplyStrategy strategy);

    [[nodiscard]] bool canStart() const override;

protected:
    [[nodiscard]] QString invalidArgumentsMessage() const override;
    [[nodiscard]] QDBusMessage kmailMethodCall() const override;
    [[nodiscard]] QString kmailCallErrorMessage(const QString &error) const override;
    void kmailCallFinished(const QDBusPendingCall &reply) override;

private:
    qint64 mItemId = -1;
    ReplyStrategy mReplyStrategy = ReplyStrategy::ReplySmart;
};
