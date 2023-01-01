/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdowndemowidget.h"
#include "markdownpreviewwidget.h"
#include <QFile>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>

MarkdownDemoWidget::MarkdownDemoWidget(QWidget *parent)
    : QWidget(parent)
{
    auto vboxLayout = new QVBoxLayout(this);
    auto mainLayout = new QHBoxLayout;
    vboxLayout->addLayout(mainLayout);
    mEdit = new QTextEdit(this);
    mEdit->setAcceptRichText(false);
    mainLayout->addWidget(mEdit);
    mPreview = new MarkdownPreviewWidget(this);
    mainLayout->addWidget(mPreview);

    connect(mEdit, &QTextEdit::textChanged, [this]() {
        mPreview->slotUpdatePreview(mEdit->toPlainText());
    });

    QFile defaultTextFile(QStringLiteral(":/test.txt"));
    defaultTextFile.open(QIODevice::ReadOnly);
    mEdit->setPlainText(QString::fromUtf8(defaultTextFile.readAll()));
}
