/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "reactiontoinvitationdialogtest.h"
#include "../calendar/reactiontoinvitationdialog.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QLabel>
#include <KPIMTextEdit/PlainTextEditorWidget>
#include <QStandardPaths>

ReactionToInvitationDialogTest::ReactionToInvitationDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
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
