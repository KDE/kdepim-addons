/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ZOOMLABEL_H
#define ZOOMLABEL_H

#include <QLabel>

class ZoomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ZoomLabel(QWidget *parent = nullptr);
    ~ZoomLabel();

    void setZoomLabel(int value);
};

#endif // ZOOMLABEL_H
