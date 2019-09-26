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

#include "quicktextsnippetgroup.h"
#include <QHBoxLayout>
#include <QLabel>
#include <KLocalizedString>
#include <QLineEdit>

QuickTextSnippetGroup::QuickTextSnippetGroup(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *lab = new QLabel(i18n("Name:"), this);
    lab->setObjectName(QStringLiteral("name"));
    mainLayout->addWidget(lab);

    mGroupNameLineEdit = new QLineEdit(this);
    mGroupNameLineEdit->setObjectName(QStringLiteral("groupnamelineedit"));
    mainLayout->addWidget(mGroupNameLineEdit);
}

QuickTextSnippetGroup::~QuickTextSnippetGroup()
{
}

void QuickTextSnippetGroup::setGroupName(const QString &name)
{
    mGroupNameLineEdit->setText(name);
}

QString QuickTextSnippetGroup::groupName() const
{
    return mGroupNameLineEdit->text();
}
