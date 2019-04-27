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

#include "markdowncreateimagewidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>

MarkdownCreateImageWidget::MarkdownCreateImageWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mTitle = new QLineEdit(this);
    mTitle->setObjectName(QStringLiteral("title"));
    mImageUrl = new QLineEdit(this);
    mImageUrl->setObjectName(QStringLiteral("image"));

    mAlternateText = new QLineEdit(this);
    mAlternateText->setObjectName(QStringLiteral("alternatetext"));


    mainLayout->addRow(i18n("Title:"), mTitle);
    mainLayout->addRow(i18n("Image Link:"), mImageUrl);
    mainLayout->addRow(i18n("Alternate text:"), mAlternateText);
    //TODO add image size too
}

MarkdownCreateImageWidget::~MarkdownCreateImageWidget()
{
}

QString MarkdownCreateImageWidget::linkStr() const
{
    if (mTitle->text().trimmed().isEmpty() && mImageUrl->text().trimmed().isEmpty()) {
        return {};
    }
    if (!mAlternateText->text().trimmed().isEmpty()) {
        return QStringLiteral("![%1](%2 \"%3\")").arg(mTitle->text(), mImageUrl->text(), mAlternateText->text());
    } else {
        return QStringLiteral("![%1](%2)").arg(mTitle->text(), mImageUrl->text());
    }
}
