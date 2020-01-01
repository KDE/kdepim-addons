/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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
#include "grammalecteresultwidget.h"
#include "libgrammalecte_debug.h"
#include "grammalectemanager.h"
#include "grammalecteparser.h"
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
    GrammalecteResultJob *job = new GrammalecteResultJob(this);
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
