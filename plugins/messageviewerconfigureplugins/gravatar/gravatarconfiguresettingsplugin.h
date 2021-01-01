/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRAVATARCONFIGURESETTINGSPLUGIN_H
#define GRAVATARCONFIGURESETTINGSPLUGIN_H

#include <MessageViewer/MessageViewerConfigureSettingsPlugin>

#include <QVariant>

class GravatarConfigureSettingsPlugin : public MessageViewer::MessageViewerConfigureSettingsPlugin
{
    Q_OBJECT
public:
    explicit GravatarConfigureSettingsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~GravatarConfigureSettingsPlugin() override;

    void showConfigureDialog(QWidget *parent) override;
};

#endif // GRAVATARCONFIGURESETTINGSPLUGIN_H
