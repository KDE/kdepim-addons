/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"

class QDBusMessage;
class QDBusPendingCall;
class QDBusPendingCallWatcher;

// Starts KMail if needed then calls a method of its D-Bus interface
class KMailDBusToolJobBase : public ToolJobBase
{
    Q_OBJECT
public:
    explicit KMailDBusToolJobBase(QObject *parent = nullptr);
    ~KMailDBusToolJobBase() override;

protected:
    void startJob() override;
    // Message sent to KMail once it is running, built with createKMailMethodCall()
    [[nodiscard]] virtual QDBusMessage kmailMethodCall() const = 0;
    // Error text when the D-Bus call fails
    [[nodiscard]] virtual QString kmailCallErrorMessage(const QString &error) const = 0;
    // Called with the reply of a successful D-Bus call, must call finish()
    virtual void kmailCallFinished(const QDBusPendingCall &reply) = 0;

    [[nodiscard]] static QDBusMessage createKMailMethodCall(const QString &method);

private:
    void slotKMailStarted(QDBusPendingCallWatcher *watcher);
    void slotKMailCallFinished(QDBusPendingCallWatcher *watcher);
};
