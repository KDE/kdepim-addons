/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidget.h"
#include <KLineEdit>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KUrlRequester>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWhatsThis>
OpenUrlWithConfigureCreateWidget::OpenUrlWithConfigureCreateWidget(QWidget *parent)
    : QWidget{parent}
    , mEnabled(new QCheckBox(i18nc("@option:check", "Enabled"), this))
    , mServerName(new QLineEdit(this))
    , mCommandLine(new QLineEdit(this))
    , mExecutable(new KUrlRequester(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins(QMargins());

    mEnabled->setObjectName(QStringLiteral("mEnabled"));
    mainLayout->addWidget(mEnabled);

    mServerName->setObjectName(QLatin1StringView("mServerName"));
    mainLayout->addRow(i18n("Server Name:"), mServerName);
    mServerName->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mServerName);

    auto formatHelp = new QLabel(i18nc("@label:textbox", "<qt><a href=\"whatsthis1\">Argument format information…</a></qt>"), this);
    formatHelp->setObjectName(QLatin1StringView("formatHelp"));
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
    mainLayout->addWidget(formatHelp);

    mCommandLine->setObjectName(QLatin1StringView("mCommandLine"));
    mCommandLine->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Command line:"), mCommandLine);
    KLineEditEventHandler::catchReturnKey(mCommandLine);

    mExecutable->setObjectName(QLatin1StringView("mEditorRequester"));

    mExecutable->setMimeTypeFilters(
        {QStringLiteral("application/x-executable"), QStringLiteral("application/x-shellscript"), QStringLiteral("application/x-desktop")});

    mExecutable->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mExecutable->lineEdit()->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Executable:"), mExecutable);
    connect(mServerName, &QLineEdit::textChanged, this, &OpenUrlWithConfigureCreateWidget::slotInfoChanged);
    connect(mExecutable->lineEdit(), &QLineEdit::textChanged, this, &OpenUrlWithConfigureCreateWidget::slotInfoChanged);
}

OpenUrlWithConfigureCreateWidget::~OpenUrlWithConfigureCreateWidget() = default;

void OpenUrlWithConfigureCreateWidget::slotLinkClicked(const QString &link)
{
    if (link == QLatin1StringView("whatsthis1")) {
        QWhatsThis::showText(QCursor::pos(), mCommandWhatsThis);
    }
}

OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo OpenUrlWithConfigureCreateWidget::info() const
{
    OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo info;
    info.url = mServerName->text().trimmed();
    info.command = mExecutable->text().trimmed();
    info.commandLines = mCommandLine->text().trimmed();
    info.enabled = mEnabled->checkState() == Qt::Checked;
    return info;
}

void OpenUrlWithConfigureCreateWidget::setInfo(const OpenUrlWithInfo &i)
{
    mServerName->setText(i.url);
    mExecutable->setText(i.command);
    mCommandLine->setText(i.commandLines);
    mEnabled->setChecked(i.enabled);
}

bool OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo::isValid() const
{
    return !url.trimmed().isEmpty() && !command.trimmed().isEmpty();
}

void OpenUrlWithConfigureCreateWidget::slotInfoChanged()
{
    Q_EMIT updateOkButton(!mServerName->text().trimmed().isEmpty() && !mExecutable->text().trimmed().isEmpty());
}

#include "moc_openurlwithconfigurecreatewidget.cpp"
