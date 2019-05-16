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

#include "languagetoolconfigwidget.h"
#include "languagetoolmanager.h"
#include "languagetoolcombobox.h"
#include "liblanguagetool_debug.h"
#include "languagetoolgetlistoflanguagejob.h"
#include "languagetoollistoflanguagesparser.h"
#include <KLocalizedString>

#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QToolButton>

#include <KUrlRequester>
LanguageToolConfigWidget::LanguageToolConfigWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mUseLocalInstance = new QCheckBox(i18n("Use Local Instance"), this);
    mUseLocalInstance->setObjectName(QStringLiteral("uselocalinstance"));
    mainLayout->addWidget(mUseLocalInstance);

    QHBoxLayout *instanceLayout = new QHBoxLayout;
    instanceLayout->setObjectName(QStringLiteral("instancelayout"));
    instanceLayout->setContentsMargins(0, 0, 0, 0);
    mInstancePathLabel = new QLabel(i18n("Instance Path:"), this);
    mInstancePathLabel->setObjectName(QStringLiteral("instancepath"));
    mInstancePathLabel->setEnabled(false);
    instanceLayout->addWidget(mInstancePathLabel);

    mInstancePath = new QLineEdit(this);
    mInstancePath->setObjectName(QStringLiteral("instancepath"));
    mInstancePath->setEnabled(false);
    mInstancePath->setClearButtonEnabled(true);
    instanceLayout->addWidget(mInstancePath);
    mainLayout->addLayout(instanceLayout);

    connect(mUseLocalInstance, &QCheckBox::clicked, this, [this](bool b) {
        updateWidgets(b);
    }
            );

    QHBoxLayout *languageLayout = new QHBoxLayout;
    languageLayout->setObjectName(QStringLiteral("languagelayout"));
    QLabel *languageLabel = new QLabel(i18n("Language:"), this);
    languageLabel->setObjectName(QStringLiteral("languageLabel"));
    languageLayout->addWidget(languageLabel);

    mLanguageToolCombobox = new LanguageToolComboBox(this);
    mLanguageToolCombobox->setObjectName(QStringLiteral("languagecombobox"));
    languageLayout->addWidget(mLanguageToolCombobox);

    QToolButton *refreshButton = new QToolButton(this);
    refreshButton->setObjectName(QStringLiteral("refreshbutton"));
    refreshButton->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    refreshButton->setToolTip(i18n("Refresh"));
    languageLayout->addWidget(refreshButton);
    connect(refreshButton, &QToolButton::clicked, this, &LanguageToolConfigWidget::refreshListOfLanguages);

    mainLayout->addLayout(languageLayout);

    mainLayout->addStretch(1);
    uploadListOfLanguages();
    loadSettings();
    updateWidgets(mUseLocalInstance->isChecked());
}

LanguageToolConfigWidget::~LanguageToolConfigWidget()
{
    saveSettings();
}

void LanguageToolConfigWidget::updateWidgets(bool enabled)
{
    mInstancePathLabel->setEnabled(enabled);
    mInstancePath->setEnabled(enabled);
}

void LanguageToolConfigWidget::refreshListOfLanguages()
{
    LanguageToolGetListOfLanguageJob *job = new LanguageToolGetListOfLanguageJob(this);
    job->setUrl(LanguageToolManager::convertToLanguagePath(mInstancePath->text()));
    job->setNetworkAccessManager(LanguageToolManager::self()->networkAccessManager());
    connect(job, &LanguageToolGetListOfLanguageJob::finished, this, &LanguageToolConfigWidget::slotGetLanguagesFinished);
    connect(job, &LanguageToolGetListOfLanguageJob::error, this, &LanguageToolConfigWidget::slotGetLanguagesError);
    job->start();
}

void LanguageToolConfigWidget::loadSettings()
{
    mUseLocalInstance->setChecked(LanguageToolManager::self()->useLocalInstance());
    mInstancePath->setText(LanguageToolManager::self()->languageToolPath());
    mLanguageToolCombobox->setLanguage(LanguageToolManager::self()->language());
}

void LanguageToolConfigWidget::saveSettings()
{
    LanguageToolManager::self()->setUseLocalInstance(mUseLocalInstance->isChecked());
    LanguageToolManager::self()->setLanguageToolPath(mInstancePath->text());
    LanguageToolManager::self()->setLanguage(mLanguageToolCombobox->language());
    LanguageToolManager::self()->saveSettings();
}

void LanguageToolConfigWidget::uploadListOfLanguages()
{
    LanguageToolGetListOfLanguageJob *job = new LanguageToolGetListOfLanguageJob(this);
    job->setUrl(LanguageToolManager::self()->languageToolLanguagesPath());
    job->setNetworkAccessManager(LanguageToolManager::self()->networkAccessManager());
    connect(job, &LanguageToolGetListOfLanguageJob::finished, this, &LanguageToolConfigWidget::slotGetLanguagesFinished);
    connect(job, &LanguageToolGetListOfLanguageJob::error, this, &LanguageToolConfigWidget::slotGetLanguagesError);
    job->start();
}

void LanguageToolConfigWidget::slotGetLanguagesError(const QString &error)
{
    qCWarning(LIBLANGUAGE_PLUGIN_LOG) << "Error during loading languages from server : " << error;
}

void LanguageToolConfigWidget::slotGetLanguagesFinished(const QString &result)
{
    const QJsonDocument doc = QJsonDocument::fromJson(result.toUtf8());
    const QJsonArray fields = doc.array();
    LanguageToolListOfLanguagesParser parser;
    mLanguageToolCombobox->fillComboBox(parser.parseResult(fields));
    mLanguageToolCombobox->setLanguage(LanguageToolManager::self()->language());
}
