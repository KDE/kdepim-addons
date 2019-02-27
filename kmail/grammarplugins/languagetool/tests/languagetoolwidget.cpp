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

#include "languagetoolwidget.h"
#include "languagetoolresultjob.h"
#include "languagetoolmanager.h"
#include "languagetoolgetlistoflanguagejob.h"

#include "languagetoolparser.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>
#include <QJsonDocument>
#include <QTextBlock>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include "languagetoolresultwidget.h"

LanguageToolWidget::LanguageToolWidget(QWidget *parent)
    : QWidget(parent)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QPushButton *button = new QPushButton(QStringLiteral("Check Grammar"), this);
    mainLayout->addWidget(button);

    QPushButton *languageButton = new QPushButton(QStringLiteral("Get List Of Languages"), this);
    mainLayout->addWidget(languageButton);

    mInput = new QTextEdit(this);
    mainLayout->addWidget(mInput);

    mResultWidget = new LanguageToolResultWidget(this);
    mainLayout->addWidget(mResultWidget);
    connect(mResultWidget, &LanguageToolResultWidget::replaceText, this, &LanguageToolWidget::slotReplaceText);

    connect(button, &QPushButton::clicked, this, &LanguageToolWidget::slotCheckGrammar);
    connect(languageButton, &QPushButton::clicked, this, &LanguageToolWidget::slotGetListOfLanguages);

}

LanguageToolWidget::~LanguageToolWidget()
{
}

void LanguageToolWidget::slotReplaceText(const MessageComposer::PluginGrammarAction &act)
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

void LanguageToolWidget::slotCheckGrammar()
{
    LanguageToolResultJob *job = new LanguageToolResultJob(this);
    job->setUrl(QStringLiteral("https://languagetool.org/api/v2/check"));
    job->setNetworkAccessManager(mNetworkAccessManager);
    job->setText(mInput->toPlainText());
    job->setLanguage(QStringLiteral("fr"));
    connect(job, &LanguageToolResultJob::finished, this, &LanguageToolWidget::slotResultFinished);
    connect(job, &LanguageToolResultJob::error, this, &LanguageToolWidget::slotError);
    job->start();
}

void LanguageToolWidget::slotGetListOfLanguages()
{
    LanguageToolGetListOfLanguageJob *job = new LanguageToolGetListOfLanguageJob(this);
    job->setUrl(QStringLiteral("https://languagetool.org/api/v2/languages"));
    job->setNetworkAccessManager(mNetworkAccessManager);
    connect(job, &LanguageToolGetListOfLanguageJob::finished, this, &LanguageToolWidget::slotGetLanguagesFinished);
    connect(job, &LanguageToolGetListOfLanguageJob::error, this, &LanguageToolWidget::slotGetLanguagesError);
    job->start();
}

void LanguageToolWidget::slotError()
{
    qDebug() << " error !!!!";
}

void LanguageToolWidget::slotGetLanguagesError()
{
    qDebug() << " error !!!!";
}


void LanguageToolWidget::slotGetLanguagesFinished(const QString &result)
{
    qDebug() << " result " << result;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonArray fields = doc.array();
    qDebug() << " fields =" << fields;
}

void LanguageToolWidget::slotResultFinished(const QString &result)
{
    qDebug() << " result" << result;
    mResultWidget->setText(mInput->toPlainText());
    LanguageToolParser parser;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonObject fields = doc.object();
    mResultWidget->applyGrammarResult(parser.parseResult(fields));
}
