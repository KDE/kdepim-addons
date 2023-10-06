/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorCheckBeforeSend>
#include <QVariant>

class ConfirmAddressPlugin : public MessageComposer::PluginEditorCheckBeforeSend
{
    Q_OBJECT
public:
    explicit ConfirmAddressPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~ConfirmAddressPlugin() override;

    MessageComposer::PluginEditorCheckBeforeSendInterface *createInterface(QObject *parent) override;
    [[nodiscard]] bool hasConfigureDialog() const override;

    void showConfigureDialog(QWidget *parent) override;
};
