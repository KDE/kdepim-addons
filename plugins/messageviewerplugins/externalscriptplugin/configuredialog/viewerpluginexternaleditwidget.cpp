/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditwidget.h"
#include <KLocalizedString>
#include <KLineEdit>
#include <QFormLayout>
#include <KUrlRequester>

ViewerPluginExternalEditWidget::ViewerPluginExternalEditWidget(QWidget *parent)
    : QWidget(parent)
{
    auto *mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

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

    mExecutable = new KUrlRequester(this);
    mExecutable->setObjectName(QStringLiteral("mEditorRequester"));

    mExecutable->setMimeTypeFilters({QStringLiteral("application/x-executable"),
                                     QStringLiteral("application/x-shellscript"),
                                     QStringLiteral("application/x-desktop")});

    mExecutable->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mExecutable->lineEdit()->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Executable:"), mExecutable);
    connect(mName, &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
    connect(mExecutable->lineEdit(), &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
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
