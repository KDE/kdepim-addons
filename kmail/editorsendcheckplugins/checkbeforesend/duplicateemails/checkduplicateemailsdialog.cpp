/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkduplicateemailsdialog.h"

#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QLabel>
#include <KConfigGroup>
#include <KSharedConfig>

CheckDuplicateEmailsDialog::CheckDuplicateEmailsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Duplicated emails"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *lab = new QLabel(i18n("These emails are duplicated. Do you want to send email?"), this);
    lab->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(lab);

    mListWidget = new QListWidget(this);
    mListWidget->setObjectName(QStringLiteral("listwidget"));
    mainLayout->addWidget(mListWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
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
    KConfigGroup group(KSharedConfig::openConfig(), "CheckDuplicateEmailsDialog");
    group.writeEntry("Size", size());
}

void CheckDuplicateEmailsDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "CheckDuplicateEmailsDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
