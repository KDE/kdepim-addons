/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageViewer/MessageViewerConfigureSettingsPlugin>

#include <QVariant>

class DkimConfigureSettingsPlugin : public MessageViewer::MessageViewerConfigureSettingsPlugin
{
    Q_OBJECT
public:
    explicit DkimConfigureSettingsPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~DkimConfigureSettingsPlugin() override;

    void showConfigureDialog(QWidget *parent) override;
};
