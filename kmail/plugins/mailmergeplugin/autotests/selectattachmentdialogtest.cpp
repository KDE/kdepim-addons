/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "selectattachmentdialogtest.h"
#include "../widgets/selectattachmentdialog.h"
#include <KUrlRequester>
#include <QLabel>
#include <QTest>
SelectAttachmentDialogTest::SelectAttachmentDialogTest(QObject *parent)
    : QObject(parent)
{
}

SelectAttachmentDialogTest::~SelectAttachmentDialogTest()
{
}

void SelectAttachmentDialogTest::shouldHaveDefaultValue()
{
    MailMerge::SelectAttachmentDialog dlg;
    QLabel *lab = dlg.findChild<QLabel *>(QStringLiteral("selectattachment_label"));
    QVERIFY(lab);
    KUrlRequester *urlRequester = dlg.findChild<KUrlRequester *>(QStringLiteral("urlrequester"));
    QVERIFY(urlRequester);
}

QTEST_MAIN(SelectAttachmentDialogTest)

#include "moc_selectattachmentdialogtest.cpp"
