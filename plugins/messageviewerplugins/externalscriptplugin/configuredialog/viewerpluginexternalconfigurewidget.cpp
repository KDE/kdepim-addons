/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternalconfigurewidget.h"
#include <QVBoxLayout>
#include <QStandardPaths>
#include <KLocalizedString>
#include "../viewerpluginexternalscriptsloadjob.h"
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

ViewerPluginExternalConfigureWidget::ViewerPluginExternalConfigureWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("layout"));
    mainLayout->setMargin(0);

    QVBoxLayout *listLayout = new QVBoxLayout;
    mainLayout->addLayout(listLayout);
    QLabel *lab = new QLabel(i18n("External Script:"), this);
    lab->setObjectName(QStringLiteral("lab"));
    listLayout->addWidget(lab);

    mListExternal = new QListWidget(this);
    mListExternal->setObjectName(QStringLiteral("listexternal"));
    listLayout->addWidget(mListExternal);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);

    mAddScript = new QPushButton(i18n("Add Script..."), this);
    mAddScript->setObjectName(QStringLiteral("addscript"));
    buttonLayout->addWidget(mAddScript);

    mModifyScript = new QPushButton(i18n("Modify Script..."), this);
    mModifyScript->setObjectName(QStringLiteral("modifyscript"));
    buttonLayout->addWidget(mModifyScript);

    mRemoveScript = new QPushButton(i18n("Remove Script"), this);
    mRemoveScript->setObjectName(QStringLiteral("removescript"));
    buttonLayout->addWidget(mRemoveScript);
}

ViewerPluginExternalConfigureWidget::~ViewerPluginExternalConfigureWidget()
{

}

void ViewerPluginExternalConfigureWidget::load()
{

    ViewerPluginExternalScriptsLoadJob job;
    const QStringList lst = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, QStringLiteral("messageviewerplugins/"), QStandardPaths::LocateDirectory);
    job.setExternalScriptsDirectories(lst);
    job.start();
    const QVector<ViewerPluginExternalScriptInfo> scriptInfos = job.scriptInfos();

}

void ViewerPluginExternalConfigureWidget::save()
{

}

void ViewerPluginExternalConfigureWidget::reset()
{

}
