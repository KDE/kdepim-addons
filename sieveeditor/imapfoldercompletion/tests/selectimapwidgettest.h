/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

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

#ifndef SELECTIMAPWIDGETTEST_H
#define SELECTIMAPWIDGETTEST_H

#include <QWidget>
#include <KSieveUi/AbstractMoveImapFolderWidget>

class DefaultMoveImapFolderWidget : public KSieveUi::AbstractMoveImapFolderWidget
{
public:
    explicit DefaultMoveImapFolderWidget(QWidget *parent = nullptr);

    void setText(const QString &str) override;
    QString text() const override;
    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account) override;
};

class SelectImapWidgetTest : public QWidget
{
    Q_OBJECT
public:
    explicit SelectImapWidgetTest(QWidget *parent = nullptr);
    ~SelectImapWidgetTest();
};

#endif // SELECTIMAPWIDGETTEST_H
