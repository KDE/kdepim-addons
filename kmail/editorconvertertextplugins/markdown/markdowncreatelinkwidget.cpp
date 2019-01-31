/*
    Copyright (C) 2019 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "markdowncreatelinkwidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>

MarkdownCreateLinkWidget::MarkdownCreateLinkWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mTitle = new QLineEdit(this);
    mTitle->setObjectName(QStringLiteral("title"));
    mLink = new QLineEdit(this);
    mLink->setObjectName(QStringLiteral("link"));


    mainLayout->addRow(i18n("Title:"), mTitle);
    mainLayout->addRow(i18n("Link:"), mLink);
}

MarkdownCreateLinkWidget::~MarkdownCreateLinkWidget()
{

}

QString MarkdownCreateLinkWidget::linkStr() const
{
    //TODO
    return {};
}
