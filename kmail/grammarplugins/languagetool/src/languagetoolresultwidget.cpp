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

#include "grammarresulttextedit.h"
#include "languagetoolresultwidget.h"
#include "languagetoolparser.h"
#include "languagetoolmanager.h"
#include "languagetoolresultjob.h"
#include <QJsonDocument>
#include <QTextEdit>

LanguagetoolResultWidget::LanguagetoolResultWidget(QWidget *parent)
    : GrammarResultWidget(parent)
{
}

LanguagetoolResultWidget::~LanguagetoolResultWidget()
{
}

void LanguagetoolResultWidget::checkGrammar()
{
    LanguagetoolResultJob *job = new LanguagetoolResultJob(this);
    job->setUrl(LanguagetoolManager::self()->languageToolPath());
    job->setNetworkAccessManager(LanguagetoolManager::self()->networkAccessManager());
    job->setText(mResult->toPlainText());
    job->setLanguage(LanguagetoolManager::self()->language());
    connect(job, &LanguagetoolResultJob::finished, this, &LanguagetoolResultWidget::slotCheckGrammarFinished);
    connect(job, &LanguagetoolResultJob::error, this, &LanguagetoolResultWidget::slotError);
    job->start();
}

void LanguagetoolResultWidget::slotCheckGrammarFinished(const QString &result)
{
    LanguageToolParser parser;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonObject fields = doc.object();
    applyGrammarResult(parser.parseResult(fields));
}

void LanguagetoolResultWidget::slotError()
{
    //TODO
}
