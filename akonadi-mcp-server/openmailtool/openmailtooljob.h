/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"

class QDBusPendingCallWatcher;

class OpenMailToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit OpenMailToolJob(QObject *parent = nullptr);
    ~OpenMailToolJob() override;

    void setItemId(qint64 id);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotKMailStarted(QDBusPendingCallWatcher *watcher);
    void slotShowMailResult(QDBusPendingCallWatcher *watcher);
    qint64 mItemId = -1;
};
