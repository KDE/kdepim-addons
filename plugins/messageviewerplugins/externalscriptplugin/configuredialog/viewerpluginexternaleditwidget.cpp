/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditwidget.h"
#include <KLineEdit>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KUrlRequester>
#include <QFormLayout>
#include <QLabel>
#include <QWhatsThis>

ViewerPluginExternalEditWidget::ViewerPluginExternalEditWidget(QWidget *parent)
    : QWidget(parent)
    , mName(new QLineEdit(this))
    , mDescription(new QLineEdit(this))
    , mCommandLine(new QLineEdit(this))
    , mExecutable(new KUrlRequester(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    mName->setObjectName(QLatin1StringView("name"));
    mainLayout->addRow(i18n("Name:"), mName);
    KLineEditEventHandler::catchReturnKey(mName);

    mDescription->setObjectName(QLatin1StringView("description"));
    mainLayout->addRow(i18n("Description:"), mDescription);
    KLineEditEventHandler::catchReturnKey(mDescription);

    mCommandLine->setClearButtonEnabled(true);
    mCommandLine->setObjectName(QLatin1StringView("commandline"));
    mCommandLine->setPlaceholderText(i18n("Add command arguments..."));
    mainLayout->addRow(i18n("Command Line:"), mCommandLine);
    KLineEditEventHandler::catchReturnKey(mCommandLine);

    auto formatHelp = new QLabel(i18n("<qt><a href=\"whatsthis1\">Argument format information...</a></qt>"), this);
    formatHelp->setObjectName(QLatin1StringView("formatHelp"));
    formatHelp->setContextMenuPolicy(Qt::NoContextMenu);
    connect(formatHelp, &QLabel::linkActivated, this, &ViewerPluginExternalEditWidget::slotLinkClicked);

    mCommandWhatsThis = i18n(
        "<qt><p><strong>These expressions may be used for the arguments:"
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

    mExecutable->setObjectName(QLatin1StringView("mEditorRequester"));

    mExecutable->setMimeTypeFilters(
        {QStringLiteral("application/x-executable"), QStringLiteral("application/x-shellscript"), QStringLiteral("application/x-desktop")});

    mExecutable->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mExecutable->lineEdit()->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Executable:"), mExecutable);
    connect(mName, &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
    connect(mExecutable->lineEdit(), &QLineEdit::textChanged, this, &ViewerPluginExternalEditWidget::slotInfoChanged);
}

ViewerPluginExternalEditWidget::~ViewerPluginExternalEditWidget() = default;

void ViewerPluginExternalEditWidget::slotLinkClicked(const QString &link)
{
    if (link == QLatin1StringView("whatsthis1")) {
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

#include "moc_viewerpluginexternaleditwidget.cpp"
