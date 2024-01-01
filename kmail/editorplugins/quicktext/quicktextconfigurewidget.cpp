/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextconfigurewidget.h"
#include "quicktextwidget.h"
#include <MailCommon/SnippetWidget>
#include <QVBoxLayout>

QuickTextConfigureWidget::QuickTextConfigureWidget(QWidget *parent)
    : QWidget(parent)
    , mSnippetWidget(new QuickTextWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    mSnippetWidget->setObjectName(QLatin1StringView("snippetwidget"));

    mainLayout->addWidget(mSnippetWidget);
}

QuickTextConfigureWidget::~QuickTextConfigureWidget() = default;

void QuickTextConfigureWidget::save()
{
    mSnippetWidget->save();
}

void QuickTextConfigureWidget::importQuickText()
{
    mSnippetWidget->importQuickText();
}

void QuickTextConfigureWidget::exportQuickText()
{
    mSnippetWidget->exportQuickText();
}

#include "moc_quicktextconfigurewidget.cpp"
