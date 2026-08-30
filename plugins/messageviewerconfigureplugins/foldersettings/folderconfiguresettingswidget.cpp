/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingswidget.h"
#include "folderconfiguresettingspagewidget.h"
#include "folderconfiguretreewidget.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QHBoxLayout>
#include <QSplitter>
using namespace Qt::Literals::StringLiterals;
namespace
{
const char myFolderConfigureSettingsWidgetGroupName[] = "FolderConfigureSettingsWidget";
}
FolderConfigureSettingsWidget::FolderConfigureSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , mFolderConfigureTreeWidget(new FolderConfigureTreeWidget(this))
    , mFolderConfigureSettingsPageWidget(new FolderConfigureSettingsPageWidget(this))
    , mSplitter(new QSplitter(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    // TODO add label ?

    mSplitter->setObjectName("splitter"_L1);
    mSplitter->setChildrenCollapsible(false);
    mainLayout->addWidget(mSplitter);

    mFolderConfigureTreeWidget->setObjectName("mFolderConfigureTreeWidget"_L1);
    mSplitter->addWidget(mFolderConfigureTreeWidget);

    mFolderConfigureSettingsPageWidget->setObjectName("mFolderConfigureSettingsPageWidget"_L1);
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
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myFolderConfigureSettingsWidgetGroupName));
    const QList<int> defaultSizes{200, 400};
    const QList<int> sizes = grp.readEntry("SplitterSize", defaultSizes);
    mSplitter->setSizes(sizes);
}

void FolderConfigureSettingsWidget::saveConfig()
{
    const QList<int> sizes = mSplitter->sizes();
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myFolderConfigureSettingsWidgetGroupName));
    grp.writeEntry("SplitterSize", sizes);
}

#include "moc_folderconfiguresettingswidget.cpp"
