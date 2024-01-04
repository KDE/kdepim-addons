/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterwidget.h"
#include <QVBoxLayout>
#include <TextCustomEditor/RichTextBrowser>

AdblockViewFilterWidget::AdblockViewFilterWidget(QWidget *parent)
    : QWidget{parent}
    , mRichTextBrowser(new TextCustomEditor::RichTextBrowser(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(mRichTextBrowser);
    // TODO
}

AdblockViewFilterWidget::~AdblockViewFilterWidget() = default;

#include "moc_adblockviewfilterwidget.cpp"
