/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/kmaildbustooljobbase.h"
#include <Akonadi/Collection>

class EditMailToolJob : public KMailDBusToolJobBase
{
    Q_OBJECT
public:
    explicit EditMailToolJob(QObject *parent = nullptr);
    ~EditMailToolJob() override;

    void setItemId(qint64 id);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;
    [[nodiscard]] QDBusMessage kmailMethodCall() const override;
    [[nodiscard]] QString kmailCallErrorMessage(const QString &error) const override;
    void kmailCallFinished(const QDBusPendingCall &reply) override;

private:
    void slotItemFetchResult(KJob *job);
    void slotDraftsCollectionResult(KJob *job);
    Akonadi::Collection mParentCollection;
    qint64 mItemId = -1;
};
