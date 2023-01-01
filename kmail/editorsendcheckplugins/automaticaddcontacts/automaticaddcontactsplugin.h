/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorCheckBeforeSend>

class AutomaticAddContactsPlugin : public MessageComposer::PluginEditorCheckBeforeSend
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~AutomaticAddContactsPlugin() override;

    MessageComposer::PluginEditorCheckBeforeSendInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;
};
