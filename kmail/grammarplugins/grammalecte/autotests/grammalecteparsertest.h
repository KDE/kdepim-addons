/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTEPARSERTEST_H
#define GRAMMALECTEPARSERTEST_H

#include <QObject>

class GrammalecteParserTest : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteParserTest(QObject *parent = nullptr);
    ~GrammalecteParserTest() = default;
private Q_SLOTS:
    void shouldParseJson_data();
    void shouldParseJson();
};

#endif // GRAMMALECTEPARSERTEST_H
