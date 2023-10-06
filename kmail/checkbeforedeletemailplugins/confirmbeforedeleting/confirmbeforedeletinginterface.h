/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] Akonadi::Item::List exec(const Akonadi::Item::List &list) override;
    [[nodiscard]] QList<QAction *> actions() const override;
    void createActions(KActionCollection *ac) override;

private:
    void slotConfigure();
    QList<QAction *> mAction;
};
