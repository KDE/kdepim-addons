/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateanswerseditorwidget.h"

#include <QPlainTextEdit>
#include <QVBoxLayout>

AutoGenerateAnswersEditorWidget::AutoGenerateAnswersEditorWidget(QWidget *parent)
    : QWidget{parent}
    , mPlainTextEdit(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mPlainTextEdit->setObjectName(QStringLiteral("mPlainTextEdit"));
    mPlainTextEdit->setReadOnly(true);
    mainLayout->addWidget(mPlainTextEdit);
}

void AutoGenerateAnswersEditorWidget::setAnswer(const QString &str)
{
    mPlainTextEdit->setPlainText(str);
}

AutoGenerateAnswersEditorWidget::~AutoGenerateAnswersEditorWidget() = default;

#include "moc_autogenerateanswerseditorwidget.cpp"
