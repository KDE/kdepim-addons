/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTLOSEINFORMATIONWARNINGTEST_H
#define MERGECONTACTLOSEINFORMATIONWARNINGTEST_H

#include <QObject>

class MergeContactLoseInformationWarningTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactLoseInformationWarningTest(QObject *parent = nullptr);
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEmitSignals();
};

#endif // MERGECONTACTLOSEINFORMATIONWARNINGTEST_H
