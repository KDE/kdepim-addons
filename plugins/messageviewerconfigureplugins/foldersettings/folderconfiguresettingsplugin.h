/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef FOLDERCONFIGURESETTINGSPLUGIN_H
#define FOLDERCONFIGURESETTINGSPLUGIN_H

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

#endif // FOLDERCONFIGURESETTINGSPLUGIN_H
