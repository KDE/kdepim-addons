/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "selectimapwidget.h"
#include <KLineEdit>
#include <KLocalizedString>
#include <QToolButton>
#include <QHBoxLayout>


SelectImapWidget::SelectImapWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    mLineEdit = new KLineEdit(this);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    layout->addWidget(mLineEdit);

    mToolButton = new QToolButton(this);
    mToolButton->setText(QStringLiteral("..."));
    mToolButton->setObjectName(QStringLiteral("toolbutton"));
    layout->addWidget(mToolButton);
}

SelectImapWidget::~SelectImapWidget()
{

}
