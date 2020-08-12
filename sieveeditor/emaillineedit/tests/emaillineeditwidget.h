/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EMAILLINEEDITWIDGET_H
#define EMAILLINEEDITWIDGET_H

#include <QWidget>
class EmailLineEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EmailLineEditWidget(QWidget *parent = nullptr);
    ~EmailLineEditWidget() = default;
};

#endif // EMAILLINEEDITWIDGET_H
