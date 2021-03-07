/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAVATARUPDATEJOBTEST_H
#define GRAVATARUPDATEJOBTEST_H

#include <QObject>

class GravatarUpdateJobTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarUpdateJobTest(QObject *parent = nullptr);
    ~GravatarUpdateJobTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // GRAVATARUPDATEJOBTEST_H
