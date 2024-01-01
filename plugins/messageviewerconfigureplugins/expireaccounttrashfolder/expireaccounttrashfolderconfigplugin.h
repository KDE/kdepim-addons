/*
   SPDX-FileCopyrightText: 2020-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

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
