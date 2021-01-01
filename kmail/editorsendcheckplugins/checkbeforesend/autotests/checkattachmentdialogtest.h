/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKATTACHMENTDIALOGTEST_H
#define CHECKATTACHMENTDIALOGTEST_H

#include <QObject>

class CheckAttachmentDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckAttachmentDialogTest(QObject *parent = nullptr);
    ~CheckAttachmentDialogTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAddEmails();
};

#endif // CHECKATTACHMENTDIALOGTEST_H
