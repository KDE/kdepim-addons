/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "grammalectewidget.h"
#include "grammalecteresultjob.h"

#include "grammalecteparser.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>
#include <QJsonDocument>
#include <QTextBlock>
#include "grammalecteresultwidget.h"

GrammalecteWidget::GrammalecteWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

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
    GrammalecteGenerateConfigOptionJob *job = new GrammalecteGenerateConfigOptionJob(this);
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
    GrammalecteResultJob *job = new GrammalecteResultJob(this);
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
