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
#include <KLocalizedString>

#include <QVBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QVariant>

#include <KUrlRequester>
LanguageToolConfigWidget::LanguageToolConfigWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mUseLocalInstance = new QCheckBox(i18n("Use Local Instance"), this);
    mUseLocalInstance->setObjectName(QStringLiteral("uselocalinstance"));
    mainLayout->addWidget(mUseLocalInstance);

    QHBoxLayout *instanceLayout = new QHBoxLayout;
    instanceLayout->setObjectName(QStringLiteral("instancelayout"));
    instanceLayout->setMargin(0);
    QLabel *instancePathLabel = new QLabel(i18n("Instance Path:"), this);
    instancePathLabel->setObjectName(QStringLiteral("instancepath"));
    instancePathLabel->setEnabled(false);
    instanceLayout->addWidget(instancePathLabel);

    mInstancePath = new QLineEdit(this);
    mInstancePath->setObjectName(QStringLiteral("instancepath"));
    mInstancePath->setEnabled(false);
    instanceLayout->addWidget(mInstancePath);
    mainLayout->addLayout(instanceLayout);

    connect(mUseLocalInstance, &QCheckBox::clicked, this, [this, instancePathLabel](bool b) {
        instancePathLabel->setEnabled(b);
        mInstancePath->setEnabled(b);
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
    mainLayout->addLayout(languageLayout);

    mainLayout->addStretch(1);
    loadSettings();
}

LanguageToolConfigWidget::~LanguageToolConfigWidget()
{
    saveSettings();
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
}
