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

#include <KMessageBox>
#include <KLocalizedString>

#include <QJsonDocument>
#include <QTextEdit>

LanguageToolResultWidget::LanguageToolResultWidget(QWidget *parent)
    : GrammarResultWidget(parent)
{
}

LanguageToolResultWidget::~LanguageToolResultWidget()
{
}

void LanguageToolResultWidget::checkGrammar()
{
    LanguageToolResultJob *job = new LanguageToolResultJob(this);
    job->setUrl(LanguageToolManager::self()->languageToolPath());
    job->setNetworkAccessManager(LanguageToolManager::self()->networkAccessManager());
    job->setText(mResult->toPlainText());
    job->setLanguage(LanguageToolManager::self()->language());
    connect(job, &LanguageToolResultJob::finished, this, &LanguageToolResultWidget::slotCheckGrammarFinished);
    connect(job, &LanguageToolResultJob::error, this, &LanguageToolResultWidget::slotError);
    job->start();
}

void LanguageToolResultWidget::slotCheckGrammarFinished(const QString &result)
{
    LanguageToolParser parser;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonObject fields = doc.object();
    applyGrammarResult(parser.parseResult(fields));
}

void LanguageToolResultWidget::slotError(const QString &str)
{
    KMessageBox::error(this, i18n("An error was reported: %1", str), i18n("Failed to check grammar."));
}
