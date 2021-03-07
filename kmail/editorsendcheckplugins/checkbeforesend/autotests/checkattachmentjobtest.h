/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKATTACHMENTJOBTEST_H
#define CHECKATTACHMENTJOBTEST_H

#include <QObject>

class CheckAttachmentJobTest : public QObject
{
    Q_OBJECT
public:
    explicit CheckAttachmentJobTest(QObject *parent = nullptr);
    ~CheckAttachmentJobTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignEmails_data();
    void shouldAssignEmails();
    void shouldRemoveDuplicatedEmails();
    void shouldRemoveDuplicatedEmails_data();
};

#endif // CHECKATTACHMENTJOBTEST_H
