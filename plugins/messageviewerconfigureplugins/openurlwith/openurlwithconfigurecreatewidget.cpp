/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

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
using namespace Qt::Literals::StringLiterals;
OpenUrlWithConfigureCreateWidget::OpenUrlWithConfigureCreateWidget(QWidget *parent)
    : QWidget{parent}
    , mEnabled(new QCheckBox(i18nc("@option:check", "Enabled"), this))
    , mServerName(new QLineEdit(this))
    , mCommandLine(new QLineEdit(this))
    , mExecutable(new KUrlRequester(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);
    mainLayout->setContentsMargins(QMargins());

    mEnabled->setObjectName(u"mEnabled"_s);
    mainLayout->addWidget(mEnabled);

    mServerName->setObjectName("mServerName"_L1);
    mainLayout->addRow(i18n("Server Name:"), mServerName);
    mServerName->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mServerName);

    auto formatHelp = new QLabel(i18nc("@label:textbox", "<qt><a href=\"whatsthis1\">Argument format information…</a></qt>"), this);
    formatHelp->setObjectName("formatHelp"_L1);
    formatHelp->setContextMenuPolicy(Qt::NoContextMenu);
    connect(formatHelp, &QLabel::linkActivated, this, &OpenUrlWithConfigureCreateWidget::slotLinkClicked);

    mCommandWhatsThis = i18n(
        "<qt><p><strong>These expressions may be used for the arguments:"
        "</strong></p>"
        "<ul>"
        "<li>%u - url used by command</li>"
        "</ul>"
        "</p></qt>");
    formatHelp->setWhatsThis(mCommandWhatsThis);
    mainLayout->addWidget(formatHelp);

    mCommandLine->setObjectName("mCommandLine"_L1);
    mCommandLine->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Command line:"), mCommandLine);
    KLineEditEventHandler::catchReturnKey(mCommandLine);

    mExecutable->setObjectName("mEditorRequester"_L1);

    mExecutable->setMimeTypeFilters({u"application/x-executable"_s, u"application/x-shellscript"_s, u"application/x-desktop"_s});

    mExecutable->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mExecutable->lineEdit()->setClearButtonEnabled(true);
    mainLayout->addRow(i18n("Executable:"), mExecutable);
    connect(mServerName, &QLineEdit::textChanged, this, &OpenUrlWithConfigureCreateWidget::slotInfoChanged);
    connect(mExecutable->lineEdit(), &QLineEdit::textChanged, this, &OpenUrlWithConfigureCreateWidget::slotInfoChanged);
}

OpenUrlWithConfigureCreateWidget::~OpenUrlWithConfigureCreateWidget() = default;

void OpenUrlWithConfigureCreateWidget::slotLinkClicked(const QString &link)
{
    if (link == "whatsthis1"_L1) {
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
