/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSPLUGIN_H
#define CONFIRMADDRESSPLUGIN_H

#include <QVariant>
#include <MessageComposer/PluginEditorCheckBeforeSend>

class ConfirmAddressPlugin : public MessageComposer::PluginEditorCheckBeforeSend
{
    Q_OBJECT
public:
    explicit ConfirmAddressPlugin(QObject *parent = nullptr, const QList<QVariant> & =
    {
    });
    ~ConfirmAddressPlugin() override;

    MessageComposer::PluginEditorCheckBeforeSendInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasConfigureDialog() const override;

    void showConfigureDialog(QWidget *parent) override;
};

#endif // CONFIRMADDRESSPLUGIN_H
