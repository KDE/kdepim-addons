/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRAVATARUPDATEWIDGETTEST_H
#define GRAVATARUPDATEWIDGETTEST_H
#include <QObject>

class GravatarUpdateWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarUpdateWidgetTest(QObject *parent = nullptr);
    ~GravatarUpdateWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAffectEmail();
};

#endif // GRAVATARUPDATEWIDGETTEST_H
