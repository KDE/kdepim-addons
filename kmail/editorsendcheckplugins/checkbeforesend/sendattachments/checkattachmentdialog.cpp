/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkattachmentdialog.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QListWidget>

CheckAttachmentDialog::CheckAttachmentDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Check Attachment"));
    auto *mainLayout = new QVBoxLayout(this);

    QLabel *lab = new QLabel(i18n("Do you want to send some attachment?"), this);
    lab->setObjectName(QStringLiteral("lab"));
    mainLayout->addWidget(lab);

    mListWidget = new QListWidget(this);
    mListWidget->setObjectName(QStringLiteral("listwidget"));
    mainLayout->addWidget(mListWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CheckAttachmentDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckAttachmentDialog::reject);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

CheckAttachmentDialog::~CheckAttachmentDialog()
{
    writeConfig();
}

void CheckAttachmentDialog::setEmails(const QStringList &emails)
{
    mListWidget->clear();
    mListWidget->addItems(emails);
}

void CheckAttachmentDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "CheckAttachmentDialog");
    group.writeEntry("Size", size());
}

void CheckAttachmentDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "CheckAttachmentDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
