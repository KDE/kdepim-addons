/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateanswerseditorwidget.h"

#include <QVBoxLayout>

AutoGenerateAnswersEditorWidget::AutoGenerateAnswersEditorWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
}

AutoGenerateAnswersEditorWidget::~AutoGenerateAnswersEditorWidget() = default;
