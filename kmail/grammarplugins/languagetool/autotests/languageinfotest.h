/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGEINFOTEST_H
#define LANGUAGEINFOTEST_H

#include <QObject>

class LanguageInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit LanguageInfoTest(QObject *parent = nullptr);
    ~LanguageInfoTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};

#endif // LANGUAGEINFOTEST_H
