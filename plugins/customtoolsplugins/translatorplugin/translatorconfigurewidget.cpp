/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfigurewidget.h"
#include <KLocalizedString>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

TranslatorConfigureWidget::TranslatorConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mEngine(new QComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mEngine->setObjectName(QStringLiteral("mEngine"));
    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);

    auto label = new QLabel(i18n("Engine:"), this);
    label->setObjectName(QStringLiteral("label"));
    hboxLayout->addWidget(label);
    hboxLayout->addWidget(mEngine);
}

TranslatorConfigureWidget::~TranslatorConfigureWidget()
{
}
