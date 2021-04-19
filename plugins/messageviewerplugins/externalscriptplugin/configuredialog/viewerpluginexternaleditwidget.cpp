/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditwidget.h"
#include <KLineEdit>
#include <KLocalizedString>
#include <KUrlRequester>
#include <QFormLayout>
#include <QLabel>
#include <QWhatsThis>

ViewerPluginExternalEditWidget::ViewerPluginExternalEditWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QFormLayout(this);
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

    auto formatHelp = new QLabel(i18n("<qt><a href=\"whatsthis1\">Argument format information...</a></qt>"), this);
    formatHelp->setObjectName(QStringLiteral("formatHelp"));
    formatHelp->setContextMenuPolicy(Qt::NoContextMenu);
    connect(formatHelp, &QLabel::linkActivated, this, &ViewerPluginExternalEditWidget::slotLinkClicked);

    mCommandWhatsThis = i18n(
        "<qt><p><strong>These expressions may be used for the date:"
        "</strong></p>"
        "<ul>"
        "<li>%s - the subject of message</li>"
        "<li>%from - the from email address</li>"
        "<li>%cc - the list of cc email address</li>"
        "<li>%bcc - the list of bcc email address</li>"
        "<li>%body - the body of message</li>"
        "<li>%inreplyto - the reply email address</li>"
        "<li>%akonadiUrl - the akonadi url (as akonadi:?item=187020)</li>"
        "</ul>"
        "</strong></p></qt>");
    formatHelp->setWhatsThis(mCommandWhatsThis);

    mainLayout->addWidget(formatHelp);

    mExecutable = new KUrlRequester(this);
    mExecutable->setObjectName(QStringLiteral("mEditorRequester"));

    mExecutable->setMimeTypeFilters(
        {QStringLiteral("application/x-executable"), QStringLiteral("application/x-shellscript"), QStringLiteral("application/x-desktop")});

    mExecutable->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mExecutable->lineEdit()->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Executable:"), mExecutable);
    connect(mName, &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
    connect(mExecutable->lineEdit(), &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
}

ViewerPluginExternalEditWidget::~ViewerPluginExternalEditWidget()
{
}

void ViewerPluginExternalEditWidget::slotLinkClicked(const QString &link)
{
    if (link == QLatin1String("whatsthis1")) {
        QWhatsThis::showText(QCursor::pos(), mCommandWhatsThis);
    }
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
