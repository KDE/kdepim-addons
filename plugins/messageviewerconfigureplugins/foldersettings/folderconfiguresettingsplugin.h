/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageViewer/MessageViewerConfigureSettingsPlugin>

#include <QVariant>

class FolderConfigureSettingsPlugin : public MessageViewer::MessageViewerConfigureSettingsPlugin
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~FolderConfigureSettingsPlugin() override;

    void showConfigureDialog(QWidget *parent) override;
};
