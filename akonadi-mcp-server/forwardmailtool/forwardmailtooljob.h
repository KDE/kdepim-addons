/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/kmaildbustooljobbase.h"

class ForwardMailToolJob : public KMailDBusToolJobBase
{
    Q_OBJECT
public:
    explicit ForwardMailToolJob(QObject *parent = nullptr);
    ~ForwardMailToolJob() override;

    void setItemId(qint64 id);
    void setAsAttachment(bool asAttachment);

    [[nodiscard]] bool canStart() const override;

protected:
    [[nodiscard]] QString invalidArgumentsMessage() const override;
    [[nodiscard]] QDBusMessage kmailMethodCall() const override;
    [[nodiscard]] QString kmailCallErrorMessage(const QString &error) const override;
    void kmailCallFinished(const QDBusPendingCall &reply) override;

private:
    qint64 mItemId = -1;
    bool mAsAttachment = false;
};
