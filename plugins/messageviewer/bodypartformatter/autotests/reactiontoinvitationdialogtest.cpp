/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "reactiontoinvitationdialogtest.h"
#include "../calendar/reactiontoinvitationdialog.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QLabel>
#include <kpimtextedit/plaintexteditorwidget.h>

ReactionToInvitationDialogTest::ReactionToInvitationDialogTest(QObject *parent)
    : QObject(parent)
{
}

ReactionToInvitationDialogTest::~ReactionToInvitationDialogTest()
{
}

void ReactionToInvitationDialogTest::shouldHaveDefaultValue()
{
    ReactionToInvitationDialog w;

    QLabel *label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);

    KPIMTextEdit::PlainTextEditorWidget *mPlainTextEditor = w.findChild<KPIMTextEdit::PlainTextEditorWidget *>(QStringLiteral("plaintexteditor"));
    QVERIFY(mPlainTextEditor);
    QVERIFY(mPlainTextEditor->toPlainText().isEmpty());

    QDialogButtonBox *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QVERIFY(w.comment().isEmpty());
}

QTEST_MAIN(ReactionToInvitationDialogTest)
