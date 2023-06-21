/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingspagewidget.h"
#include "folderconfiguremodifycollectionjob.h"
#include "folderconfiguresettingsexperywidget.h"
#include "folderconfiguresettingsgeneralwidget.h"
#include "folderconfiguresettingstemplatewidget.h"
#include "folderconfiguresettingsviewwidget.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <MailCommon/CollectionExpiryWidget>
#include <QTabWidget>
#include <QVBoxLayout>

FolderConfigureSettingsPageWidget::FolderConfigureSettingsPageWidget(QWidget *parent)
    : QWidget(parent)
    , mCollectionExpiryWidget(new FolderConfigureSettingsExperyWidget(this))
    , mFolderConfigureSettingsGeneralWidget(new FolderConfigureSettingsGeneralWidget(this))
    , mCollectionTemplateWidget(new FolderConfigureSettingsTemplateWidget(this))
    , mFolderConfigureSettingsViewWidget(new FolderConfigureSettingsViewWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto tab = new QTabWidget(this);
    tab->setObjectName(QStringLiteral("tab"));
    mainLayout->addWidget(tab);

    // General
    mFolderConfigureSettingsGeneralWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsGeneralWidget"));
    tab->addTab(mFolderConfigureSettingsGeneralWidget, i18n("General"));

    // View
    mFolderConfigureSettingsViewWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsViewWidget"));
    tab->addTab(mFolderConfigureSettingsViewWidget, i18n("View"));

    // Expiry => add Tab
    mCollectionExpiryWidget->setObjectName(QStringLiteral("mCollectionExpiryWidget"));
    tab->addTab(mCollectionExpiryWidget, i18n("Expiry"));

    // Template
    mCollectionTemplateWidget->setObjectName(QStringLiteral("mCollectionTemplateWidget"));
    tab->addTab(mCollectionTemplateWidget, i18n("Template"));
}

FolderConfigureSettingsPageWidget::~FolderConfigureSettingsPageWidget() = default;

void FolderConfigureSettingsPageWidget::save(const Akonadi::Collection::List &cols)
{
    if (KMessageBox::Continue
        == KMessageBox::warningContinueCancel(this,
                                              i18n("It will override all settings for each selected folder. Do you want to continue?"),
                                              i18n("Save Folder Settings"),
                                              KStandardGuiItem::save())) {
        for (Akonadi::Collection col : cols) {
            mFolderConfigureSettingsGeneralWidget->save(col);
            mCollectionExpiryWidget->save(col);
            mFolderConfigureSettingsViewWidget->save(col);
            mCollectionTemplateWidget->save(col);
            auto job = new FolderConfigureModifyCollectionJob();
            job->setCollection(col);
            job->start();
        }
    }
}

#include "moc_folderconfiguresettingspagewidget.cpp"
