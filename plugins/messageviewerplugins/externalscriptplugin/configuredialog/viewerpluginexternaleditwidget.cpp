/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternaleditwidget.h"
#include <QVBoxLayout>
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

ViewerPluginExternalEditWidget::ViewerPluginExternalEditWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mName = new QLineEdit(this);
    mName->setObjectName(QStringLiteral("name"));
    mainLayout->addRow(i18n("Name:"), mName);

    mDescription = new QLineEdit(this);
    mDescription->setObjectName(QStringLiteral("description"));
    mainLayout->addRow(i18n("Description:"), mDescription);

    mCommandLine = new QLineEdit(this);
    mCommandLine->setClearButtonEnabled(true);
    mCommandLine->setObjectName(QStringLiteral("commandline"));
    mainLayout->addRow(i18n("Command Line:"), mCommandLine);

    mExecutable = new QLineEdit(this);
    mExecutable->setClearButtonEnabled(true);
    mExecutable->setObjectName(QStringLiteral("executable"));
    mainLayout->addRow(i18n("Executable:"), mExecutable);
    connect(mName, &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
    connect(mExecutable, &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
}

ViewerPluginExternalEditWidget::~ViewerPluginExternalEditWidget()
{

}

void ViewerPluginExternalEditWidget::slotInfoChanged()
{
    Q_EMIT scriptIsValid(!mExecutable->text().trimmed().isEmpty() && !mName->text().trimmed().isEmpty() && !mExistingsNames.contains(mName->text()));
}

void ViewerPluginExternalEditWidget::setExistingsNames(const QStringList &existingsNames)
{
    mExistingsNames = existingsNames;
}

void ViewerPluginExternalEditWidget::setScriptInfo(const ViewerPluginExternalScriptInfo &info)
{
    mScriptInfo = info;
    mName->setText(mScriptInfo.name());
    mDescription->setText(mScriptInfo.description());
    mCommandLine->setText(mScriptInfo.commandLine());
    mExecutable->setText(mScriptInfo.executable());
}

void ViewerPluginExternalEditWidget::save()
{
    mScriptInfo.setName(mName->text());
    mScriptInfo.setDescription(mDescription->text());
    mScriptInfo.setCommandLine(mCommandLine->text());
    mScriptInfo.setExecutable(mExecutable->text());
}

ViewerPluginExternalScriptInfo ViewerPluginExternalEditWidget::scriptInfo() const
{
    return mScriptInfo;
}
