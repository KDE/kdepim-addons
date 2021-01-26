/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultwidget.h"
#include "grammalectemanager.h"
#include "grammalecteparser.h"
#include "grammarresulttextedit.h"
#include "libgrammalecte_debug.h"
#include <QJsonDocument>

GrammalecteResultWidget::GrammalecteResultWidget(QWidget *parent)
    : GrammarResultWidget(parent)
{
}

GrammalecteResultWidget::~GrammalecteResultWidget()
{
}

void GrammalecteResultWidget::checkGrammar()
{
    auto *job = new GrammalecteResultJob(this);
    job->setPythonPath(GrammalecteManager::self()->pythonPath());
    job->setGrammarlecteCliPath(GrammalecteManager::self()->grammalectePath());
    job->setArguments(GrammalecteManager::self()->options());
    job->setText(mResult->toPlainText());
    connect(job, &GrammalecteResultJob::finished, this, &GrammalecteResultWidget::slotCheckGrammarFinished);
    connect(job, &GrammalecteResultJob::error, this, &GrammalecteResultWidget::slotError);
    job->start();
}

void GrammalecteResultWidget::slotCheckGrammarFinished(const QString &result)
{
    GrammalecteParser parser;
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonObject fields = doc.object();
    applyGrammarResult(parser.parseResult(fields));
}

void GrammalecteResultWidget::slotError(GrammalecteResultJob::ErrorType error)
{
    switch (error) {
    case GrammalecteResultJob::ErrorType::NoError:
        break;
    case GrammalecteResultJob::ErrorType::TextIsEmpty:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: text is empty";
        break;
    case GrammalecteResultJob::ErrorType::PythonPathMissing:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: missing python path";
        break;
    case GrammalecteResultJob::ErrorType::GrammalecteMissing:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: missing grammalectepath";
        break;
    case GrammalecteResultJob::ErrorType::Unknown:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: unknow error";
        break;
    }
}
