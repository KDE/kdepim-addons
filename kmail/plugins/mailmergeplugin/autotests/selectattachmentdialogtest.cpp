/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "selectattachmentdialogtest.h"
using namespace Qt::Literals::StringLiterals;

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
    QLabel *lab = dlg.findChild<QLabel *>(u"selectattachment_label"_s);
    QVERIFY(lab);
    KUrlRequester *urlRequester = dlg.findChild<KUrlRequester *>(u"urlrequester"_s);
    QVERIFY(urlRequester);
}

QTEST_MAIN(SelectAttachmentDialogTest)

#include "moc_selectattachmentdialogtest.cpp"
