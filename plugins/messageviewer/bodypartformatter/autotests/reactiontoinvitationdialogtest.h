/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef REACTIONTOINVITATIONDIALOGTEST_H
#define REACTIONTOINVITATIONDIALOGTEST_H

#include <QObject>

class ReactionToInvitationDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit ReactionToInvitationDialogTest(QObject *parent = nullptr);
    ~ReactionToInvitationDialogTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // REACTIONTOINVITATIONDIALOGTEST_H
