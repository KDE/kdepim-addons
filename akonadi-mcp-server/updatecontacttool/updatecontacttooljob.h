/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/tooljobbase.h"
#include <QDate>
#include <QStringList>
#include <optional>

namespace KContacts
{
class Addressee;
}

class UpdateContactToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    struct ContactChanges {
        std::optional<QString> name;
        std::optional<QStringList> emails;
        std::optional<QStringList> phoneNumbers;
        std::optional<QString> organization;
        // An invalid date clears the birthday
        std::optional<QDate> birthday;
        std::optional<QString> note;
        [[nodiscard]] bool isEmpty() const;
    };

    explicit UpdateContactToolJob(QObject *parent = nullptr);
    ~UpdateContactToolJob() override;

    [[nodiscard]] bool canStart() const override;

    void setItemId(qint64 itemId);
    void setChanges(const ContactChanges &changes);

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotItemFetchResult(KJob *job);
    void slotItemModifyResult(KJob *job);
    void applyChanges(KContacts::Addressee &contact) const;
    qint64 mItemId = -1;
    ContactChanges mChanges;
};
