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

#include "languagetoolupdatecombobox.h"
#include "languagetoolgetlistoflanguagejob.h"
#include "languagetoollistoflanguagesparser.h"
#include "languagetoolmanager.h"
#include "liblanguagetool_debug.h"
#include "languagetoolcombobox.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <QJsonArray>
#include <QJsonDocument>

LanguageToolUpdateComboBox::LanguageToolUpdateComboBox(QObject *parent)
    : QObject(parent)
{

}

LanguageToolUpdateComboBox::~LanguageToolUpdateComboBox()
{

}


void LanguageToolUpdateComboBox::checkListOfLanguagesFromSpecificPath(const QString &url)
{
    LanguageToolGetListOfLanguageJob *job = new LanguageToolGetListOfLanguageJob(this);
    job->setUrl(LanguageToolManager::convertToLanguagePath(url));
    job->setNetworkAccessManager(LanguageToolManager::self()->networkAccessManager());
    connect(job, &LanguageToolGetListOfLanguageJob::finished, this, &LanguageToolUpdateComboBox::slotGetLanguagesFinished);
    connect(job, &LanguageToolGetListOfLanguageJob::error, this, &LanguageToolUpdateComboBox::slotGetLanguagesError);
    job->start();
}

void LanguageToolUpdateComboBox::refreshListOfLanguages()
{
    LanguageToolGetListOfLanguageJob *job = new LanguageToolGetListOfLanguageJob(this);
    job->setUrl(LanguageToolManager::self()->languageToolLanguagesPath());
    job->setNetworkAccessManager(LanguageToolManager::self()->networkAccessManager());
    connect(job, &LanguageToolGetListOfLanguageJob::finished, this, &LanguageToolUpdateComboBox::slotGetLanguagesFinished);
    connect(job, &LanguageToolGetListOfLanguageJob::error, this, &LanguageToolUpdateComboBox::slotGetLanguagesError);
    job->start();
}

QWidget *LanguageToolUpdateComboBox::parentWidget() const
{
    return mParentWidget;
}

void LanguageToolUpdateComboBox::setParentWidget(QWidget *parentWidget)
{
    mParentWidget = parentWidget;
}

LanguageToolComboBox *LanguageToolUpdateComboBox::languageToolCombobox() const
{
    return mLanguageToolCombobox;
}

void LanguageToolUpdateComboBox::setLanguageToolCombobox(LanguageToolComboBox *languageToolCombobox)
{
    mLanguageToolCombobox = languageToolCombobox;
}


void LanguageToolUpdateComboBox::slotGetLanguagesError(const QString &error)
{
    qCWarning(LIBLANGUAGE_PLUGIN_LOG) << "Error during loading languages from server : " << error;
    KMessageBox::error(parentWidget(), i18n("An error was found during got languages:\n%1", error), i18n("List of Languages"));
}

void LanguageToolUpdateComboBox::slotGetLanguagesFinished(const QString &result)
{
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonArray fields = doc.array();
    LanguageToolListOfLanguagesParser parser;
    mLanguageToolCombobox->fillComboBox(parser.parseResult(fields));
    mLanguageToolCombobox->setLanguage(LanguageToolManager::self()->language());
}
