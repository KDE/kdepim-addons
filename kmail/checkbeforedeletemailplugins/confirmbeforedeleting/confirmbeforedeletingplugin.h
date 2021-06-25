/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <MessageViewer/MessageViewerCheckBeforeDeletingPlugin>

class ConfirmBeforeDeletingPlugin : public MessageViewer::MessageViewerCheckBeforeDeletingPlugin
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingPlugin(QObject *parent = nullptr);
    ~ConfirmBeforeDeletingPlugin() override;

    void showConfigureDialog(QWidget *parent) override;
};
