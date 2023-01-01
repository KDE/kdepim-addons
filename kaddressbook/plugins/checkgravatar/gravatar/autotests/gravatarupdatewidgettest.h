/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

class GravatarUpdateWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit GravatarUpdateWidgetTest(QObject *parent = nullptr);
    ~GravatarUpdateWidgetTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAffectEmail();
};
