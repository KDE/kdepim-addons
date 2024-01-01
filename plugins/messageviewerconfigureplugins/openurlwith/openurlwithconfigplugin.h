/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageViewer/MessageViewerConfigureSettingsPlugin>

#include <QVariant>

class OpenUrlWithConfigPlugin : public MessageViewer::MessageViewerConfigureSettingsPlugin
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~OpenUrlWithConfigPlugin() override;

    void showConfigureDialog(QWidget *parent) override;
};
