/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef MAILMERGEWIDGETTEST_H
#define MAILMERGEWIDGETTEST_H

#include <QObject>

class MailMergeWidgetTest : public QObject
{
    Q_OBJECT
public:
    MailMergeWidgetTest();

private Q_SLOTS:
    void shouldHaveDefaultValueOnCreation();
    void shouldEmitSourceModeChanged();
    void shouldDontEmitSourceModeChangedWhenIndexIsInvalid();
    void shouldChangeStackedWidgetIndexWhenChangeComboboxIndex();
};

#endif // MAILMERGEWIDGETTEST_H
