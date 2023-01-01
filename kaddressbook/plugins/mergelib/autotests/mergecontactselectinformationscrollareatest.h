/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactSelectInformationScrollAreaTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationScrollAreaTest(QObject *parent = nullptr);
    ~MergeContactSelectInformationScrollAreaTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
