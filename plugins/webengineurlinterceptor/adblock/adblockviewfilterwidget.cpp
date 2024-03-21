/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterwidget.h"
#include <QVBoxLayout>
#include <TextCustomEditor/RichTextBrowser>
#include <TextCustomEditor/RichTextBrowserWidget>

AdblockViewFilterWidget::AdblockViewFilterWidget(QWidget *parent)
    : QWidget{parent}
    , mRichTextBrowser(new TextCustomEditor::RichTextBrowser(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto richTextBrowerWidget = new TextCustomEditor::RichTextBrowserWidget(mRichTextBrowser, this);
    richTextBrowerWidget->setObjectName(QStringLiteral("richTextBrowerWidget"));
    mRichTextBrowser->setObjectName(QStringLiteral("mRichTextBrowser"));
    mainLayout->addWidget(richTextBrowerWidget);
}

AdblockViewFilterWidget::~AdblockViewFilterWidget() = default;

void AdblockViewFilterWidget::setFilterText(const QString &str)
{
    mRichTextBrowser->setPlainText(str);
}

#include "moc_adblockviewfilterwidget.cpp"
