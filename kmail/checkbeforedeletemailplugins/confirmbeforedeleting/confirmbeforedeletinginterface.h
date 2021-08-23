/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/MessageViewerCheckBeforeDeletingInterface>
#include <QObject>
class QAction;
class KActionCollection;
class ConfirmBeforeDeletingInterface : public MessageViewer::MessageViewerCheckBeforeDeletingInterface
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingInterface(QObject *parent = nullptr);
    ~ConfirmBeforeDeletingInterface() override;

    Q_REQUIRED_RESULT Akonadi::Item::List exec(const Akonadi::Item::List &list) override;
    Q_REQUIRED_RESULT QList<QAction *> actions() const override;

private:
    void slotConfigure();
    void createActions(KActionCollection *ac);
    QList<QAction *> mAction;
};
