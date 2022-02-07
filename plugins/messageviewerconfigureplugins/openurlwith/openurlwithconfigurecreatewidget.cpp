/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWhatsThis>
OpenUrlWithConfigureCreateWidget::OpenUrlWithConfigureCreateWidget(QWidget *parent)
    : QWidget{parent}
    , mServerName(new QLineEdit(this))
    , mCommand(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(QMargins());


    mServerName->setObjectName(QStringLiteral("mServerName"));
    mainLayout->addRow(i18n("Server Name:"), mServerName);

    auto formatHelp = new QLabel(i18n("<qt><a href=\"whatsthis1\">Argument format information...</a></qt>"), this);
    formatHelp->setObjectName(QStringLiteral("formatHelp"));
    formatHelp->setContextMenuPolicy(Qt::NoContextMenu);
    connect(formatHelp, &QLabel::linkActivated, this, &OpenUrlWithConfigureCreateWidget::slotLinkClicked);

    mCommandWhatsThis = i18n(
        "<qt><p><strong>These expressions may be used for the arguments:"
        "</strong></p>"
        "<ul>"
        "<li>%u - url used by command</li>"
        "</ul>"
        "</strong></p></qt>");
    formatHelp->setWhatsThis(mCommandWhatsThis);

    mCommand->setObjectName(QStringLiteral("mCommand"));
    mainLayout->addRow(i18n("Command:"), mCommand);
}

OpenUrlWithConfigureCreateWidget::~OpenUrlWithConfigureCreateWidget()
{
}

void OpenUrlWithConfigureCreateWidget::slotLinkClicked(const QString &link)
{
    if (link == QLatin1String("whatsthis1")) {
        QWhatsThis::showText(QCursor::pos(), mCommandWhatsThis);
    }
}

OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo OpenUrlWithConfigureCreateWidget::info() const
{
    OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo info;
    info.url = mServerName->text().trimmed();
    info.command = mCommand->text().trimmed();
    return info;
}

void OpenUrlWithConfigureCreateWidget::setInfo(const OpenUrlWithInfo &i)
{
    mServerName->setText(i.url);
    mCommand->setText(i.command);
}

bool OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo::isValid() const
{
    return !url.trimmed().isEmpty() && !command.trimmed().isEmpty();
}
