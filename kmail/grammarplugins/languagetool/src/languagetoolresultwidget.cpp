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
#include "languagetoolcombobox.h"
#include "languagetoolupdatecombobox.h"

#include <KMessageBox>
#include <KLocalizedString>

#include <QHBoxLayout>
#include <QJsonDocument>
#include <QTextEdit>

LanguageToolResultWidget::LanguageToolResultWidget(QWidget *parent)
    : GrammarResultWidget(parent)
{
    mLanguageToolUpdateCombobox = new LanguageToolUpdateComboBox(this);
    addExtraWidget();
    mLanguageToolUpdateCombobox->setLanguageToolCombobox(mLanguageToolComboBox);
    mLanguageToolUpdateCombobox->setParentWidget(this);
    mLanguageToolUpdateCombobox->refreshListOfLanguages();
}

LanguageToolResultWidget::~LanguageToolResultWidget()
{
}

void LanguageToolResultWidget::checkGrammar()
{
    LanguageToolResultJob *job = new LanguageToolResultJob(this);
    job->setUrl(LanguageToolManager::self()->languageToolCheckPath());
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


void LanguageToolResultWidget::addExtraWidget()
{
    QHBoxLayout *extraWidgetLayout = new QHBoxLayout;
    extraWidgetLayout->setObjectName(QStringLiteral("extraWidgetLayout"));
    extraWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mLanguageToolComboBox = new LanguageToolComboBox(this);
    mLanguageToolComboBox->setObjectName(QStringLiteral("languagetoolcombobox"));
    extraWidgetLayout->addWidget(mLanguageToolComboBox);
    mExtraWidgetLayout->addStretch(1);
    mExtraWidgetLayout->addLayout(extraWidgetLayout);
}
