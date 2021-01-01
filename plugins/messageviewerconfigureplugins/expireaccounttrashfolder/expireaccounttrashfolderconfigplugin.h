/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef EXPIREACCOUNTTRASHFOLDERCONFIGPLUGIN_H
#define EXPIREACCOUNTTRASHFOLDERCONFIGPLUGIN_H

#include <MessageViewer/MessageViewerConfigureSettingsPlugin>

#include <QVariant>

class ExpireAccountTrashFolderConfigPlugin : public MessageViewer::MessageViewerConfigureSettingsPlugin
{
    Q_OBJECT
public:
    explicit ExpireAccountTrashFolderConfigPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ExpireAccountTrashFolderConfigPlugin() override;

    void showConfigureDialog(QWidget *parent) override;
};

#endif // EXPIREACCOUNTTRASHFOLDERCONFIGPLUGIN_H
