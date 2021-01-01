/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef REGEXPEDITORLINEEDITTEST_H
#define REGEXPEDITORLINEEDITTEST_H

#include <QObject>

class RegexpEditorLineEditTest : public QObject
{
    Q_OBJECT
public:
    explicit RegexpEditorLineEditTest(QObject *parent = nullptr);
    ~RegexpEditorLineEditTest() = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // REGEXPEDITORLINEEDITTEST_H
