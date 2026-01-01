/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QLabel>

class ZoomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ZoomLabel(QWidget *parent = nullptr);
    ~ZoomLabel() override;

    void setZoomLabel(int value);
};
