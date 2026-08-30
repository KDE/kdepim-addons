/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockviewfilterwidget.h"
#include <QVBoxLayout>
#include <TextCustomEditor/RichTextBrowser>
#include <TextCustomEditor/RichTextBrowserWidget>
using namespace Qt::Literals::StringLiterals;

AdblockViewFilterWidget::AdblockViewFilterWidget(QWidget *parent)
    : QWidget{parent}
    , mRichTextBrowser(new TextCustomEditor::RichTextBrowser(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto richTextBrowerWidget = new TextCustomEditor::RichTextBrowserWidget(mRichTextBrowser, this);
    richTextBrowerWidget->setObjectName(u"richTextBrowerWidget"_s);
    mRichTextBrowser->setObjectName(u"mRichTextBrowser"_s);
    mainLayout->addWidget(richTextBrowerWidget);
}

AdblockViewFilterWidget::~AdblockViewFilterWidget() = default;

void AdblockViewFilterWidget::setFilterText(const QString &str)
{
    mRichTextBrowser->setPlainText(str);
}

#include "moc_adblockviewfilterwidget.cpp"
