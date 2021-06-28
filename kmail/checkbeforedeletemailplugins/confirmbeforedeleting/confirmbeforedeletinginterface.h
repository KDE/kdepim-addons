/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/MessageViewerCheckBeforeDeletingInterface>
#include <QObject>

class ConfirmBeforeDeletingInterface : public MessageViewer::MessageViewerCheckBeforeDeletingInterface
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingInterface(QObject *parent = nullptr);
    ~ConfirmBeforeDeletingInterface() override;

    Q_REQUIRED_RESULT bool exec() override;
};
