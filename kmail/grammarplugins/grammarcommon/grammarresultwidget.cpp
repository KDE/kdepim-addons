/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "grammarresulttextedit.h"
#include "grammarresultwidget.h"

#include <KLocalizedString>

#include <QHBoxLayout>
#include <QJsonDocument>
#include <QTextEdit>
#include <QToolButton>

GrammarResultWidget::GrammarResultWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mExtraWidgetLayout = new QHBoxLayout;
    mExtraWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(mExtraWidgetLayout);

    QToolButton *closeBtn = new QToolButton(this);
    closeBtn->setObjectName(QStringLiteral("close-button"));
    closeBtn->setIcon(QIcon::fromTheme(QStringLiteral("dialog-close")));
    closeBtn->setIconSize(QSize(12, 12));
    closeBtn->setToolTip(i18n("Close"));
    mExtraWidgetLayout->addWidget(closeBtn);
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
