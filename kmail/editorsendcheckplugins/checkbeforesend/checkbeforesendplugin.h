/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorCheckBeforeSend>

class CheckBeforeSendPlugin : public MessageComposer::PluginEditorCheckBeforeSend
{
    Q_OBJECT
public:
    explicit CheckBeforeSendPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~CheckBeforeSendPlugin() override;

    MessageComposer::PluginEditorCheckBeforeSendInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasConfigureDialog() const override;

    void showConfigureDialog(QWidget *parent) override;
};
