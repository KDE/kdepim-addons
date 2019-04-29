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
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QDebug>
MarkdownCreateImageWidget::MarkdownCreateImageWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mTitle = new QLineEdit(this);
    mTitle->setObjectName(QStringLiteral("title"));
    mTitle->setClearButtonEnabled(true);
    mImageUrl = new QLineEdit(this);
    mImageUrl->setObjectName(QStringLiteral("image"));
    mImageUrl->setClearButtonEnabled(true);

    mAlternateText = new QLineEdit(this);
    mAlternateText->setObjectName(QStringLiteral("alternatetext"));
    mAlternateText->setClearButtonEnabled(true);


    mainLayout->addRow(i18n("Title:"), mTitle);
    mainLayout->addRow(i18n("Image Link:"), mImageUrl);
    mainLayout->addRow(i18n("Alternate text:"), mAlternateText);

    mKeepOriginalSize = new QCheckBox(i18n("Keep original size"), this);
    mKeepOriginalSize->setObjectName(QStringLiteral("keeporiginalsize"));
    mKeepOriginalSize->setChecked(true);
    mainLayout->addRow(mKeepOriginalSize);
    connect(mKeepOriginalSize, &QCheckBox::stateChanged, this, &MarkdownCreateImageWidget::slotKeepOriginalSizeChanged);

    mLabWidth = new QLabel(i18n("Width:"), this);
    mLabWidth->setObjectName(QStringLiteral("labwidth"));
    mLabWidth->setEnabled(false);
    mWidth = new QSpinBox(this);
    mWidth->setObjectName(QStringLiteral("mwidth"));
    mWidth->setMinimum(1);
    mWidth->setMaximum(999);
    mWidth->setEnabled(false);
    mWidth->setSuffix(i18n(" px"));
    mainLayout->addRow(mLabWidth, mWidth);

    mLabHeight = new QLabel(i18n("Height:"), this);
    mLabHeight->setObjectName(QStringLiteral("labheight"));
    mLabHeight->setEnabled(false);
    mHeight = new QSpinBox(this);
    mHeight->setObjectName(QStringLiteral("mheight"));
    mHeight->setMinimum(1);
    mHeight->setMaximum(999);
    mHeight->setEnabled(false);
    mHeight->setSuffix(i18n(" px"));
    mainLayout->addRow(mLabHeight, mHeight);
}

MarkdownCreateImageWidget::~MarkdownCreateImageWidget()
{
}

void MarkdownCreateImageWidget::slotKeepOriginalSizeChanged()
{
    bool enabled = !mKeepOriginalSize->isChecked();
    mLabWidth->setEnabled(enabled);
    mWidth->setEnabled(enabled);
    mLabHeight->setEnabled(enabled);
    mHeight->setEnabled(enabled);
}

QString MarkdownCreateImageWidget::linkStr() const
{
    if (mTitle->text().trimmed().isEmpty() && mImageUrl->text().trimmed().isEmpty()) {
        return {};
    }
    QString defineSize;
    if (!mKeepOriginalSize->isChecked()) {
        defineSize = QStringLiteral(" =%1x%2").arg(mWidth->value()).arg(mHeight->value());
    }

    QString imageText = mImageUrl->text();
    if (!defineSize.isEmpty()) {
        imageText += defineSize;
    }
    if (!mAlternateText->text().trimmed().isEmpty()) {
        return QStringLiteral("![%1](%2 \"%3\")").arg(mTitle->text(), imageText, mAlternateText->text());
    } else {
        return QStringLiteral("![%1](%2)").arg(mTitle->text(), imageText);
    }
}
