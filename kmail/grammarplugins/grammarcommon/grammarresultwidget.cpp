/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresulttextedit.h"
#include "grammarresultwidget.h"

#include <KLocalizedString>

#include <QHBoxLayout>
#include <QToolButton>

GrammarResultWidget::GrammarResultWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mExtraWidgetLayout = new QHBoxLayout;
    mExtraWidgetLayout->setContentsMargins({});
    mainLayout->addLayout(mExtraWidgetLayout);

    QToolButton *closeBtn = new QToolButton(this);
    closeBtn->setObjectName(QStringLiteral("close-button"));
    closeBtn->setIcon(QIcon::fromTheme(QStringLiteral("dialog-close")));
    closeBtn->setIconSize(QSize(12, 12));
    closeBtn->setToolTip(i18n("Close"));
    mExtraWidgetLayout->addWidget(closeBtn);
    mExtraWidgetLayout->addStretch(1);
    connect(closeBtn, &QToolButton::clicked, this, &GrammarResultWidget::closeChecker);

    mResult = new GrammarResultTextEdit(this);
    mResult->setObjectName(QStringLiteral("grammarResult"));
    connect(mResult, &GrammarResultTextEdit::replaceText, this, &GrammarResultWidget::replaceText);
    connect(mResult, &GrammarResultTextEdit::checkAgain, this, &GrammarResultWidget::checkAgain);
    connect(mResult, &GrammarResultTextEdit::closeChecker, this, &GrammarResultWidget::closeChecker);
    mainLayout->addWidget(mResult);
}

GrammarResultWidget::~GrammarResultWidget()
{
}

void GrammarResultWidget::addExtraWidget()
{
}

void GrammarResultWidget::setText(const QString &str)
{
    mResult->setText(str);
}

void GrammarResultWidget::applyGrammarResult(const QVector<GrammarError> &infos)
{
    mResult->applyGrammarResult(infos);
}
