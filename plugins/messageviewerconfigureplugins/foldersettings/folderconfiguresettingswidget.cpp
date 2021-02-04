/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingswidget.h"
#include "folderconfiguresettingspagewidget.h"
#include "folderconfiguretreewidget.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QHBoxLayout>
#include <QSplitter>
namespace
{
static const char myFolderConfigureSettingsWidgetGroupName[] = "FolderConfigureSettingsWidget";
}
FolderConfigureSettingsWidget::FolderConfigureSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , mFolderConfigureTreeWidget(new FolderConfigureTreeWidget(this))
    , mFolderConfigureSettingsPageWidget(new FolderConfigureSettingsPageWidget(this))
    , mSplitter(new QSplitter(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    // TODO add label ?

    mSplitter->setObjectName(QStringLiteral("splitter"));
    mSplitter->setChildrenCollapsible(false);
    mainLayout->addWidget(mSplitter);

    mFolderConfigureTreeWidget->setObjectName(QStringLiteral("mFolderConfigureTreeWidget"));
    mSplitter->addWidget(mFolderConfigureTreeWidget);

    mFolderConfigureSettingsPageWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsPageWidget"));
    mSplitter->addWidget(mFolderConfigureSettingsPageWidget);
    readConfig();
}

FolderConfigureSettingsWidget::~FolderConfigureSettingsWidget()
{
    saveConfig();
}

void FolderConfigureSettingsWidget::save()
{
    const Akonadi::Collection::List collections = mFolderConfigureTreeWidget->listCollections();
    mFolderConfigureSettingsPageWidget->save(collections);
}

void FolderConfigureSettingsWidget::readConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myFolderConfigureSettingsWidgetGroupName);
    const QList<int> defaultSizes{200, 400};
    const QList<int> sizes = grp.readEntry("SplitterSize", defaultSizes);
    mSplitter->setSizes(sizes);
}

void FolderConfigureSettingsWidget::saveConfig()
{
    const QList<int> sizes = mSplitter->sizes();
    KConfigGroup grp(KSharedConfig::openConfig(), myFolderConfigureSettingsWidgetGroupName);
    grp.writeEntry("SplitterSize", sizes);
}
