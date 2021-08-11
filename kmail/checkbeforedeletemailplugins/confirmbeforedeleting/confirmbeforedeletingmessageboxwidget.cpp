/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxwidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>

#include <KLocalizedString>

ConfirmBeforeDeletingMessageBoxWidget::ConfirmBeforeDeletingMessageBoxWidget(QWidget *parent)
    : QWidget(parent)
    , mLabelInfo(new QLabel(this))
    , mUseSameResultForOtherCheck(new QCheckBox(i18n("Reuse..."), this)) // TODO fix i18n
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mLabelInfo->setObjectName(QStringLiteral("mLabelInfo"));
    mLabelInfo->setWordWrap(true);
    mainLayout->addWidget(mLabelInfo);

    mUseSameResultForOtherCheck->setObjectName(QStringLiteral("mUseSameResultForOtherCheck"));
    mainLayout->addWidget(mUseSameResultForOtherCheck);
}

ConfirmBeforeDeletingMessageBoxWidget::~ConfirmBeforeDeletingMessageBoxWidget()
{
}

void ConfirmBeforeDeletingMessageBoxWidget::setInfo(const QString &str)
{
    mLabelInfo->setText(str);
}

bool ConfirmBeforeDeletingMessageBoxWidget::useSameResult() const
{
    return mUseSameResultForOtherCheck->isChecked();
}
