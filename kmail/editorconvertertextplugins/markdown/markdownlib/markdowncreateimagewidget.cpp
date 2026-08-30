/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagewidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
using namespace Qt::Literals::StringLiterals;
MarkdownCreateImageWidget::MarkdownCreateImageWidget(QWidget *parent)
    : QWidget(parent)
    , mTitle(new QLineEdit(this))
    , mImageUrl(new QLineEdit(this))
    , mAlternateText(new QLineEdit(this))
    , mKeepOriginalSize(new QCheckBox(i18nc("@option:check", "Keep original size"), this))
    , mLabWidth(new QLabel(i18nc("@label:textbox", "Width:"), this))
    , mWidth(new QSpinBox(this))
    , mLabHeight(new QLabel(i18nc("@label:textbox", "Height:"), this))
    , mHeight(new QSpinBox(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);
    mainLayout->setContentsMargins({});

    mTitle->setObjectName("title"_L1);
    mTitle->setClearButtonEnabled(true);
    connect(mTitle, &QLineEdit::textChanged, this, &MarkdownCreateImageWidget::slotEnableButton);
    mImageUrl->setObjectName("image"_L1);
    mImageUrl->setClearButtonEnabled(true);
    connect(mImageUrl, &QLineEdit::textChanged, this, &MarkdownCreateImageWidget::slotEnableButton);

    mAlternateText->setObjectName("alternatetext"_L1);
    mAlternateText->setClearButtonEnabled(true);

    mainLayout->addRow(i18n("Title:"), mTitle);
    mainLayout->addRow(i18n("Image Link:"), mImageUrl);
    mainLayout->addRow(i18n("Alternate text:"), mAlternateText);

    mKeepOriginalSize->setObjectName("keeporiginalsize"_L1);
    mKeepOriginalSize->setChecked(true);
    mainLayout->addRow(mKeepOriginalSize);
    connect(mKeepOriginalSize, &QCheckBox::checkStateChanged, this, &MarkdownCreateImageWidget::slotKeepOriginalSizeChanged);

    auto sizeWidget = new QWidget;
    sizeWidget->setObjectName("sizeWidget"_L1);
    auto sizeWidgetLayout = new QHBoxLayout(sizeWidget);
    sizeWidgetLayout->setObjectName("sizeWidgetLayout"_L1);
    sizeWidgetLayout->setContentsMargins({});
    mainLayout->addRow(sizeWidget);

    mLabWidth->setObjectName("labwidth"_L1);
    mLabWidth->setEnabled(false);
    mWidth->setObjectName("mwidth"_L1);
    mWidth->setMinimum(1);
    mWidth->setMaximum(999);
    mWidth->setValue(50);
    mWidth->setEnabled(false);
    mWidth->setSuffix(i18n(" px"));
    sizeWidgetLayout->addWidget(mLabWidth);
    sizeWidgetLayout->addWidget(mWidth);

    mLabHeight->setObjectName("labheight"_L1);
    mLabHeight->setEnabled(false);
    mHeight->setObjectName("mheight"_L1);
    mHeight->setMinimum(1);
    mHeight->setMaximum(999);
    mHeight->setValue(50);
    mHeight->setEnabled(false);
    mHeight->setSuffix(i18n(" px"));
    sizeWidgetLayout->addWidget(mLabHeight);
    sizeWidgetLayout->addWidget(mHeight);
    sizeWidgetLayout->addStretch(1);
}

MarkdownCreateImageWidget::~MarkdownCreateImageWidget() = default;

void MarkdownCreateImageWidget::slotKeepOriginalSizeChanged()
{
    bool enabled = !mKeepOriginalSize->isChecked();
    mLabWidth->setEnabled(enabled);
    mWidth->setEnabled(enabled);
    mLabHeight->setEnabled(enabled);
    mHeight->setEnabled(enabled);
}

void MarkdownCreateImageWidget::slotEnableButton()
{
    Q_EMIT enabledOkButton(!mTitle->text().trimmed().isEmpty() && !mImageUrl->text().trimmed().isEmpty());
}

QString MarkdownCreateImageWidget::linkStr() const
{
    if (mTitle->text().trimmed().isEmpty() && mImageUrl->text().trimmed().isEmpty()) {
        return {};
    }
    QString defineSize;
    if (!mKeepOriginalSize->isChecked()) {
        defineSize = u" =%1x%2"_s.arg(mWidth->value()).arg(mHeight->value());
    }

    QString imageText = mImageUrl->text();
    if (!defineSize.isEmpty()) {
        imageText += defineSize;
    }
    if (!mAlternateText->text().trimmed().isEmpty()) {
        return u"![%3](%2 \"%1\")"_s.arg(mTitle->text().trimmed(), imageText, mAlternateText->text().trimmed());
    } else {
        return u"![%1](%2)"_s.arg(mTitle->text().trimmed(), imageText);
    }
}

#include "moc_markdowncreateimagewidget.cpp"
