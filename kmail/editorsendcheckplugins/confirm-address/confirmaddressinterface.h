/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSINTERFACE_H
#define CONFIRMADDRESSINTERFACE_H

#include <MessageComposer/PluginEditorCheckBeforeSendInterface>
#include <QHash>
class ConfirmAddressInterface : public MessageComposer::PluginEditorCheckBeforeSendInterface
{
    Q_OBJECT
public:
    explicit ConfirmAddressInterface(QObject *parent = nullptr);
    ~ConfirmAddressInterface() override;
    bool exec(const MessageComposer::PluginEditorCheckBeforeSendParams &params) override;

Q_SIGNALS:
    void forceReloadConfig();

public Q_SLOTS:
    void reloadConfig() override;

private:
    void slotAddWhiteListEmails(const QStringList &lst, uint currentIdentity);

    struct ConfirmAddressSettings {
        QStringList mDomains;
        QStringList mWhiteLists;
        bool mRejectedDomain = false;
    };

    QHash<uint, ConfirmAddressSettings> mHashSettings;
};

#endif // CONFIRMADDRESSINTERFACE_H
