/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmessageboxwidgettest.h"
#include "confirmbeforedeletingmessageboxwidget.h"
#include <QCheckBox>
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(ConfirmBeforeDeletingMessageBoxWidgetTest)
ConfirmBeforeDeletingMessageBoxWidgetTest::ConfirmBeforeDeletingMessageBoxWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void ConfirmBeforeDeletingMessageBoxWidgetTest::shouldHaveDefaultValues()
{
    ConfirmBeforeDeletingMessageBoxWidget w;
    // TODO

#if 0
    , mLabelInfo(new QLabel(this))
    , mUseSameResultForOtherCheck(new QCheckBox(i18n("Reuse..."), this)) //TODO fix i18n
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mLabelInfo->setObjectName(QStringLiteral("mLabelInfo"));
    mLabelInfo->setWordWrap(true);
    mainLayout->addWidget(mLabelInfo);

    mUseSameResultForOtherCheck->setObjectName(QStringLiteral("mUseSameResultForOtherCheck"));
    mainLayout->addWidget(mUseSameResultForOtherCheck);
#endif
}
