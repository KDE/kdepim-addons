/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    KMessageBox::error(parentWidget(), i18n("An error occurred attempting to load the list of available languages:\n%1", error), i18n("List of Languages"));
}

void LanguageToolUpdateComboBox::slotGetLanguagesFinished(const QString &result)
{
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonArray fields = doc.array();
    LanguageToolListOfLanguagesParser parser;
    mLanguageToolCombobox->fillComboBox(parser.parseResult(fields));
    mLanguageToolCombobox->setLanguage(LanguageToolManager::self()->language());
}
