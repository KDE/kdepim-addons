/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagewidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
MarkdownCreateImageWidget::MarkdownCreateImageWidget(QWidget *parent)
    : QWidget(parent)
    , mTitle(new QLineEdit(this))
    , mImageUrl(new QLineEdit(this))
    , mAlternateText(new QLineEdit(this))
    , mKeepOriginalSize(new QCheckBox(i18n("Keep original size"), this))
    , mLabWidth(new QLabel(i18nc("@label:textbox", "Width:"), this))
    , mWidth(new QSpinBox(this))
    , mLabHeight(new QLabel(i18nc("@label:textbox", "Height:"), this))
    , mHeight(new QSpinBox(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    mTitle->setObjectName(QLatin1StringView("title"));
    mTitle->setClearButtonEnabled(true);
    connect(mTitle, &QLineEdit::textChanged, this, &MarkdownCreateImageWidget::slotEnableButton);
    mImageUrl->setObjectName(QLatin1StringView("image"));
    mImageUrl->setClearButtonEnabled(true);
    connect(mImageUrl, &QLineEdit::textChanged, this, &MarkdownCreateImageWidget::slotEnableButton);

    mAlternateText->setObjectName(QLatin1StringView("alternatetext"));
    mAlternateText->setClearButtonEnabled(true);

    mainLayout->addRow(i18n("Title:"), mTitle);
    mainLayout->addRow(i18n("Image Link:"), mImageUrl);
    mainLayout->addRow(i18n("Alternate text:"), mAlternateText);

    mKeepOriginalSize->setObjectName(QLatin1StringView("keeporiginalsize"));
    mKeepOriginalSize->setChecked(true);
    mainLayout->addRow(mKeepOriginalSize);
#if QT_VERSION < QT_VERSION_CHECK(6, 7, 0)
    connect(mKeepOriginalSize, &QCheckBox::stateChanged, this, &MarkdownCreateImageWidget::slotKeepOriginalSizeChanged);
#else
    connect(mKeepOriginalSize, &QCheckBox::checkStateChanged, this, &MarkdownCreateImageWidget::slotKeepOriginalSizeChanged);
#endif

    auto sizeWidget = new QWidget;
    sizeWidget->setObjectName(QLatin1StringView("sizeWidget"));
    auto sizeWidgetLayout = new QHBoxLayout(sizeWidget);
    sizeWidgetLayout->setObjectName(QLatin1StringView("sizeWidgetLayout"));
    sizeWidgetLayout->setContentsMargins({});
    mainLayout->addRow(sizeWidget);

    mLabWidth->setObjectName(QLatin1StringView("labwidth"));
    mLabWidth->setEnabled(false);
    mWidth->setObjectName(QLatin1StringView("mwidth"));
    mWidth->setMinimum(1);
    mWidth->setMaximum(999);
    mWidth->setValue(50);
    mWidth->setEnabled(false);
    mWidth->setSuffix(i18n(" px"));
    sizeWidgetLayout->addWidget(mLabWidth);
    sizeWidgetLayout->addWidget(mWidth);

    mLabHeight->setObjectName(QLatin1StringView("labheight"));
    mLabHeight->setEnabled(false);
    mHeight->setObjectName(QLatin1StringView("mheight"));
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
        defineSize = QStringLiteral(" =%1x%2").arg(mWidth->value()).arg(mHeight->value());
    }

    QString imageText = mImageUrl->text();
    if (!defineSize.isEmpty()) {
        imageText += defineSize;
    }
    if (!mAlternateText->text().trimmed().isEmpty()) {
        return QStringLiteral("![%1](%2 \"%3\")").arg(mTitle->text().trimmed(), imageText, mAlternateText->text().trimmed());
    } else {
        return QStringLiteral("![%1](%2)").arg(mTitle->text().trimmed(), imageText);
    }
}

#include "moc_markdowncreateimagewidget.cpp"
