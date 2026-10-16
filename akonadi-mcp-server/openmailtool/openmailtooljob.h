/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/kmaildbustooljobbase.h"

class OpenMailToolJob : public KMailDBusToolJobBase
{
    Q_OBJECT
public:
    explicit OpenMailToolJob(QObject *parent = nullptr);
    ~OpenMailToolJob() override;

    void setItemId(qint64 id);

    [[nodiscard]] bool canStart() const override;

protected:
    [[nodiscard]] QString invalidArgumentsMessage() const override;
    [[nodiscard]] QDBusMessage kmailMethodCall() const override;
    [[nodiscard]] QString kmailCallErrorMessage(const QString &error) const override;
    void kmailCallFinished(const QDBusPendingCall &reply) override;

private:
    qint64 mItemId = -1;
};
