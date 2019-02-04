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
#include "grammarresultjob.h"
#include "grammalecteparser.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>
#include <QJsonDocument>
#include "grammarresultwidget.h"

GrammalecteWidget::GrammalecteWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QPushButton *button = new QPushButton(QStringLiteral("Check Grammar"), this);
    mainLayout->addWidget(button);

    mInput = new QTextEdit(this);
    mainLayout->addWidget(mInput);

    mResultWidget = new GrammarResultWidget(this);
    mainLayout->addWidget(mResultWidget);

    connect(button, &QPushButton::clicked, this, &GrammalecteWidget::slotCheckGrammar);
}

GrammalecteWidget::~GrammalecteWidget()
{

}

void GrammalecteWidget::slotCheckGrammar()
{
    GrammarResultJob *job = new GrammarResultJob(this);
    job->setPythonPath(QStringLiteral("/usr/bin/python3"));
    job->setGrammarlecteCliPath(QStringLiteral("/compile/kde5/framework/kde/pim/grammalecte/grammalecte-cli.py"));
    job->setArguments(QStringList() << QStringLiteral("-j"));
    job->setText(mInput->toPlainText());
    connect(job, &GrammarResultJob::finished, this, &GrammalecteWidget::slotResultFinished);
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
