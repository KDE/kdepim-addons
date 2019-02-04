/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#ifndef GRAMMALECTECONFIGWIDGET_H
#define GRAMMALECTECONFIGWIDGET_H

#include <QWidget>
#include "libgrammalect_private_export.h"
class LIBGRAMMALECTPRIVATE_TESTS_EXPORT GrammalecteConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammalecteConfigWidget(QWidget *parent = nullptr);
    ~GrammalecteConfigWidget();
    void loadSettings();
    void saveSettings();
private:
    void loadGrammarSettings();
    QWidget *addGeneralTab();
    QWidget *addGrammarTab();
};

#endif // GRAMMALECTECONFIGWIDGET_H
