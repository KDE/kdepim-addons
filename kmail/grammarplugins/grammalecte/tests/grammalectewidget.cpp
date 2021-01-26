/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectewidget.h"
#include "grammalecteresultjob.h"

#include "grammalecteparser.h"
#include "grammalecteresultwidget.h"
#include <QDebug>
#include <QJsonDocument>
#include <QPushButton>
#include <QTextBlock>
#include <QTextEdit>
#include <QVBoxLayout>

GrammalecteWidget::GrammalecteWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QVBoxLayout(this);

    QPushButton *button = new QPushButton(QStringLiteral("Check Grammar"), this);
    mainLayout->addWidget(button);

    QPushButton *checkSettingsButton = new QPushButton(QStringLiteral("Get Settings"), this);
    mainLayout->addWidget(checkSettingsButton);

    mInput = new QTextEdit(this);
    mainLayout->addWidget(mInput);

    mResultWidget = new GrammalecteResultWidget(this);
    mainLayout->addWidget(mResultWidget);
    connect(mResultWidget, &GrammalecteResultWidget::replaceText, this, &GrammalecteWidget::slotReplaceText);

    connect(button, &QPushButton::clicked, this, &GrammalecteWidget::slotCheckGrammar);
    connect(checkSettingsButton, &QPushButton::clicked, this, &GrammalecteWidget::slotGetSettings);
}

GrammalecteWidget::~GrammalecteWidget()
{
}

void GrammalecteWidget::slotReplaceText(const MessageComposer::PluginGrammarAction &act)
{
    QTextBlock block = mInput->document()->findBlockByNumber(act.blockId() - 1);
    if (block.isValid()) {
        QTextCursor cur(block);
        const int position = cur.position() + act.start();
        cur.setPosition(position);
        cur.setPosition(position + act.length(), QTextCursor::KeepAnchor);
        cur.insertText(act.replacement());
    }
}

void GrammalecteWidget::slotGetSettings()
{
    auto *job = new GrammalecteGenerateConfigOptionJob(this);
    job->setPythonPath(QStringLiteral("/usr/bin/python3"));
    job->setGrammarlecteCliPath(QStringLiteral("/compile/kde5/framework/kde/pim/grammalecte/grammalecte-cli.py"));
    connect(job, &GrammalecteGenerateConfigOptionJob::finished, this, &GrammalecteWidget::slotGetSettingsFinished);
    job->start();
}

void GrammalecteWidget::slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result)
{
}

void GrammalecteWidget::slotCheckGrammar()
{
    auto *job = new GrammalecteResultJob(this);
    job->setPythonPath(QStringLiteral("/usr/bin/python3"));
    job->setGrammarlecteCliPath(QStringLiteral("/compile/kde5/framework/kde/pim/grammalecte/grammalecte-cli.py"));
    job->setText(mInput->toPlainText());
    connect(job, &GrammalecteResultJob::finished, this, &GrammalecteWidget::slotResultFinished);
    job->start();
}

void GrammalecteWidget::slotResultFinished(const QString &result)
{
    qDebug() << " result" << result;
    mResultWidget->setText(mInput->toPlainText());
    GrammalecteParser parser;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonObject fields = doc.object();
    mResultWidget->applyGrammarResult(parser.parseResult(fields));
}
