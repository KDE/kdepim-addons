/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSPLUGIN_H
#define AUTOMATICADDCONTACTSPLUGIN_H

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

#endif // AUTOMATICADDCONTACTSPLUGIN_H
