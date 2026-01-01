/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <MessageViewer/MessageViewerCheckBeforeDeletingPlugin>
#include <QVariant>

class ConfirmBeforeDeletingPlugin : public MessageViewer::MessageViewerCheckBeforeDeletingPlugin
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~ConfirmBeforeDeletingPlugin() override;

    void showConfigureDialog(QWidget *parent) override;
    [[nodiscard]] MessageViewer::MessageViewerCheckBeforeDeletingInterface *createInterface(QObject *parent) override;
};
