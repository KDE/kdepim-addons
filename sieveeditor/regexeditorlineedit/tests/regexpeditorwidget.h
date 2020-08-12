/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef REGEXPEDITORWIDGET_H
#define REGEXPEDITORWIDGET_H

#include <QWidget>
class RegExpEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegExpEditorWidget(QWidget *parent = nullptr);
    ~RegExpEditorWidget() = default;
};

#endif // REGEXPEDITORWIDGET_H
