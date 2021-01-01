/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

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

    auto *label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);

    auto *mPlainTextEditor = w.findChild<KPIMTextEdit::PlainTextEditorWidget *>(QStringLiteral("plaintexteditor"));
    QVERIFY(mPlainTextEditor);
    QVERIFY(mPlainTextEditor->toPlainText().isEmpty());

    auto *buttonBox = w.findChild<QDialogButtonBox *>(QStringLiteral("buttonbox"));
    QVERIFY(buttonBox);

    QVERIFY(w.comment().isEmpty());
}

QTEST_MAIN(ReactionToInvitationDialogTest)
