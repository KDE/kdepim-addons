/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultwidget.h"
#include "grammalectemanager.h"
#include "grammalecteparser.h"
#include "grammarresulttextedit.h"
#include "libgrammalecte_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QJsonDocument>

GrammalecteResultWidget::GrammalecteResultWidget(QWidget *parent)
    : GrammarResultWidget(parent)
{
}

GrammalecteResultWidget::~GrammalecteResultWidget() = default;

void GrammalecteResultWidget::checkGrammar()
{
    auto job = new GrammalecteResultJob(this);
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
    QString str;
    switch (error) {
    case GrammalecteResultJob::ErrorType::NoError:
        break;
    case GrammalecteResultJob::ErrorType::TextIsEmpty:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: text is empty";
        break;
    case GrammalecteResultJob::ErrorType::PythonPathMissing:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: missing python path";
        str = i18n("Python path is missing.");
        break;
    case GrammalecteResultJob::ErrorType::GrammalecteMissing:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: missing grammalectepath";
        str = i18n("Grammalecte path not found.");
        break;
    case GrammalecteResultJob::ErrorType::Unknown:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: unknown error";
        break;
    case GrammalecteResultJob::ErrorType::PythonPathNotExist:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: python exec doesn't exist";
        str = i18n("Grammalecte program file not found.");
        break;
    case GrammalecteResultJob::ErrorType::GrammarlectCliNotExist:
        qCWarning(LIBGRAMMALECTE_PLUGIN_LOG) << "An error found during executing GrammalecteResultJob: grammalecte cli not found.";
        str = i18n("Grammalecte cli file not found.");
        break;
    }
    if (!str.isEmpty()) {
        KMessageBox::error(this, str, i18n("Grammalecte error"));
    }
}
