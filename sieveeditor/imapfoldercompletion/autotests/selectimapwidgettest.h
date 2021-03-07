/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPWIDGETTEST_H
#define SELECTIMAPWIDGETTEST_H

#include <QObject>

class SelectImapWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapWidgetTest(QObject *parent = nullptr);
    ~SelectImapWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignText();
};

#endif // SELECTIMAPWIDGETTEST_H
