/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    auto *job = new LanguageToolResultJob(this);
    job->setUrl(LanguageToolManager::self()->languageToolCheckPath());
    job->setNetworkAccessManager(LanguageToolManager::self()->networkAccessManager());
    job->setText(mResult->toPlainText());
    job->setLanguage(/*LanguageToolManager::self()->language()*/ mLanguageToolComboBox->language());
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
    auto *extraWidgetLayout = new QHBoxLayout;
    extraWidgetLayout->setObjectName(QStringLiteral("extraWidgetLayout"));
    extraWidgetLayout->setContentsMargins({});
    mLanguageToolComboBox = new LanguageToolComboBox(this);
    mLanguageToolComboBox->setObjectName(QStringLiteral("languagetoolcombobox"));
    extraWidgetLayout->addWidget(mLanguageToolComboBox);
    mExtraWidgetLayout->addLayout(extraWidgetLayout);
}
