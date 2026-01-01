/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateanswerseditorwidget.h"
#include "autogenerateanswerseditortextedit.h"

#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
AutoGenerateAnswersEditorWidget::AutoGenerateAnswersEditorWidget(QWidget *parent)
    : QWidget{parent}
    , mTextEdit(new AutoGenerateAnswersEditorTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mTextEdit->setObjectName(u"mTextEdit"_s);
    mTextEdit->setReadOnly(true);
    mainLayout->addWidget(mTextEdit);

    connect(mTextEdit, &AutoGenerateAnswersEditorTextEdit::insertText, this, &AutoGenerateAnswersEditorWidget::insertText);
}

AutoGenerateAnswersEditorWidget::~AutoGenerateAnswersEditorWidget() = default;

void AutoGenerateAnswersEditorWidget::setAnswer(const QString &str)
{
    mTextEdit->setText(str);
}

#include "moc_autogenerateanswerseditorwidget.cpp"
