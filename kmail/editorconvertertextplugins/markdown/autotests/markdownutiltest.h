/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class MarkdownUtilTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownUtilTest(QObject *parent = nullptr);
    ~MarkdownUtilTest() override = default;
private Q_SLOTS:
    void shouldConvert();
    void shouldConvert_data();
};
