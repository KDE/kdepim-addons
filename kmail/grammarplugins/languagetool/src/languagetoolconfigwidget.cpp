/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigwidget.h"
#include "languagetoolcombobox.h"
#include "languagetoolgetlistoflanguagejob.h"
#include "languagetoollistoflanguagesparser.h"
#include "languagetoolmanager.h"
#include "languagetoolupdatecombobox.h"
#include "liblanguagetool_debug.h"
#include <KLocalizedString>

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

LanguageToolConfigWidget::LanguageToolConfigWidget(QWidget *parent)
    : QWidget(parent)
    , mUseLocalInstance(new QCheckBox(i18n("Use Local Instance"), this))
    , mInstancePath(new QLineEdit(this))
    , mInstancePathLabel(new QLabel(i18n("Instance Path:"), this))
    , mLanguageToolCombobox(new LanguageToolComboBox(this))
    , mLanguageToolUpdateCombobox(new LanguageToolUpdateComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mUseLocalInstance->setObjectName(QStringLiteral("uselocalinstance"));
    mainLayout->addWidget(mUseLocalInstance);

    auto instanceLayout = new QHBoxLayout;
    instanceLayout->setObjectName(QStringLiteral("instancelayout"));
    instanceLayout->setContentsMargins({});
    mInstancePathLabel->setObjectName(QStringLiteral("instancepath"));
    mInstancePathLabel->setEnabled(false);
    instanceLayout->addWidget(mInstancePathLabel);

    mInstancePath->setObjectName(QStringLiteral("instancepath"));
    mInstancePath->setEnabled(false);
    mInstancePath->setClearButtonEnabled(true);
    instanceLayout->addWidget(mInstancePath);
    mainLayout->addLayout(instanceLayout);

    connect(mUseLocalInstance, &QCheckBox::clicked, this, &LanguageToolConfigWidget::updateWidgets);

    auto languageLayout = new QHBoxLayout;
    languageLayout->setObjectName(QStringLiteral("languagelayout"));
    auto languageLabel = new QLabel(i18n("Language:"), this);
    languageLabel->setObjectName(QStringLiteral("languageLabel"));
    languageLayout->addWidget(languageLabel);

    mLanguageToolCombobox->setObjectName(QStringLiteral("languagecombobox"));
    languageLayout->addWidget(mLanguageToolCombobox);
    mLanguageToolUpdateCombobox->setLanguageToolCombobox(mLanguageToolCombobox);
    mLanguageToolUpdateCombobox->setParentWidget(this);

    auto refreshButton = new QToolButton(this);
    refreshButton->setObjectName(QStringLiteral("refreshbutton"));
    refreshButton->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    refreshButton->setToolTip(i18n("Refresh"));
    languageLayout->addWidget(refreshButton);
    connect(refreshButton, &QToolButton::clicked, this, [this]() {
        if (LanguageToolManager::self()->allowToGetListOfLanguages()) {
            mLanguageToolUpdateCombobox->checkListOfLanguagesFromSpecificPath(mInstancePath->text());
        }
    });

    mainLayout->addLayout(languageLayout);

    mainLayout->addStretch(1);
    mLanguageToolUpdateCombobox->refreshListOfLanguages();
    loadSettings();
    updateWidgets(mUseLocalInstance->isChecked());
    connect(this, &LanguageToolConfigWidget::resetValue, this, &LanguageToolConfigWidget::slotResetValue);
}

LanguageToolConfigWidget::~LanguageToolConfigWidget()
{
    saveSettings();
}

void LanguageToolConfigWidget::slotResetValue()
{
    mUseLocalInstance->setChecked(false);
    mInstancePath->setText(QStringLiteral("https://api.languagetoolplus.com/v2"));
    updateWidgets(false);
}

void LanguageToolConfigWidget::updateWidgets(bool enabled)
{
    mInstancePathLabel->setEnabled(enabled);
    mInstancePath->setEnabled(enabled);
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
