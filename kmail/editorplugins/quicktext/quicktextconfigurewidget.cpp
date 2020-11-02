/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextconfigurewidget.h"
#include "quicktextwidget.h"
#include <QVBoxLayout>
#include <KLocalizedString>
#include <MailCommon/SnippetWidget>

QuickTextConfigureWidget::QuickTextConfigureWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mSnippetWidget = new QuickTextWidget(this);
    mSnippetWidget->setObjectName(QStringLiteral("snippetwidget"));

    mainLayout->addWidget(mSnippetWidget);
}

QuickTextConfigureWidget::~QuickTextConfigureWidget()
{
}

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
