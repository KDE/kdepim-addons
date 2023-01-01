/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
