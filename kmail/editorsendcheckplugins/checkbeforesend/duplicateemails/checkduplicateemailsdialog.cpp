/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkduplicateemailsdialog.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigCheckDuplicateEmailsDialog[] = "CheckDuplicateEmailsDialog";
}
CheckDuplicateEmailsDialog::CheckDuplicateEmailsDialog(QWidget *parent)
    : QDialog(parent)
    , mListWidget(new QListWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Duplicated emails"));
    auto mainLayout = new QVBoxLayout(this);
    auto lab = new QLabel(i18n("These emails are duplicated. Do you want to send email?"), this);
    lab->setObjectName(QLatin1StringView("label"));
    mainLayout->addWidget(lab);

    mListWidget->setObjectName(QLatin1StringView("listwidget"));
    mainLayout->addWidget(mListWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CheckDuplicateEmailsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckDuplicateEmailsDialog::reject);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

CheckDuplicateEmailsDialog::~CheckDuplicateEmailsDialog()
{
    writeConfig();
}

void CheckDuplicateEmailsDialog::setDuplicatedEmails(const QMap<QString, int> &emails)
{
    QMapIterator<QString, int> i(emails);
    while (i.hasNext()) {
        i.next();
        mListWidget->addItem(i18nc("emails (number of emails)", "%1 (%2)", i.key(), i.value()));
    }
}

void CheckDuplicateEmailsDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigCheckDuplicateEmailsDialog));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void CheckDuplicateEmailsDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigCheckDuplicateEmailsDialog));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

#include "moc_checkduplicateemailsdialog.cpp"
