/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxwidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>

#include <KLocalizedString>
#include <QStyle>
#include <QStyleOption>

ConfirmBeforeDeletingMessageBoxWidget::ConfirmBeforeDeletingMessageBoxWidget(QWidget *parent)
    : QWidget(parent)
    , mLabelInfo(new QLabel(this))
    , mUseSameResultForOtherCheck(new QCheckBox(i18nc("@option:check", "Apply to All"), this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    mainLayout->setContentsMargins({});

    const QIcon tmpIcon = style()->standardIcon(QStyle::SP_MessageBoxQuestion, nullptr, this);
    auto iconLabel = new QLabel(this);
    iconLabel->setObjectName(QLatin1StringView("iconLabel"));
    if (!tmpIcon.isNull()) {
        QStyleOption option;
        option.initFrom(this);
        iconLabel->setPixmap(tmpIcon.pixmap(style()->pixelMetric(QStyle::PM_MessageBoxIconSize, &option, this)));
    }
    mainLayout->addWidget(iconLabel);

    auto textLayout = new QVBoxLayout;
    textLayout->setObjectName(QLatin1StringView("textLayout"));
    textLayout->setContentsMargins({});

    mainLayout->addLayout(textLayout);

    mLabelInfo->setObjectName(QLatin1StringView("mLabelInfo"));
    mLabelInfo->setWordWrap(true);
    textLayout->addWidget(mLabelInfo, Qt::AlignTop);

    mUseSameResultForOtherCheck->setObjectName(QLatin1StringView("mUseSameResultForOtherCheck"));
    textLayout->addWidget(mUseSameResultForOtherCheck);

    mUseSameResultForOtherCheck->setChecked(false);
}

ConfirmBeforeDeletingMessageBoxWidget::~ConfirmBeforeDeletingMessageBoxWidget() = default;

void ConfirmBeforeDeletingMessageBoxWidget::setInfo(const QString &str)
{
    mLabelInfo->setText(str);
}

bool ConfirmBeforeDeletingMessageBoxWidget::useSameResult() const
{
    return mUseSameResultForOtherCheck->isChecked();
}

#include "moc_confirmbeforedeletingmessageboxwidget.cpp"
