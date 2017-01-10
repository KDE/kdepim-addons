/*
   Copyright (C) 2013-2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef ADBLOCKLISTWIDGET_H
#define ADBLOCKLISTWIDGET_H

#include <QListWidget>

class QPaintEvent;
class QEvent;
namespace AdBlock
{
class AdBlockListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AdBlockListWidget(QWidget *parent = nullptr);
    ~AdBlockListWidget();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;
private:
    void generalPaletteChanged();
    QColor mTextColor;
};
}

#endif // ADBLOCKLISTWIDGET_H
