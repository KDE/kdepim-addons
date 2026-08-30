/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

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
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
namespace
{
const char myConfigCheckDuplicateEmailsDialog[] = "CheckDuplicateEmailsDialog";
}
CheckDuplicateEmailsDialog::CheckDuplicateEmailsDialog(QWidget *parent)
    : QDialog(parent)
    , mListWidget(new QListWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Duplicated emails"));
    auto mainLayout = new QVBoxLayout(this);
    auto lab = new QLabel(i18nc("@label:textbox", "These emails are duplicated. Do you want to send email?"), this);
    lab->setObjectName("label"_L1);
    mainLayout->addWidget(lab);

    mListWidget->setObjectName("listwidget"_L1);
    mainLayout->addWidget(mListWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonbox"_L1);
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
    mListWidget->clear();
    for (const auto &[key, value] : emails.asKeyValueRange()) {
        mListWidget->addItem(i18nc("emails (number of emails)", "%1 (%2)", key, value));
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
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfigCheckDuplicateEmailsDialog), 500, 300);
}

#include "moc_checkduplicateemailsdialog.cpp"
