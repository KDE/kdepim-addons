/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "checkattachmentdialog.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

CheckAttachmentDialog::CheckAttachmentDialog(QWidget *parent)
    : QDialog(parent)
    , mListWidget(new QListWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Check Attachment"));
    auto mainLayout = new QVBoxLayout(this);

    auto lab = new QLabel(i18n("Do you want to send some attachment?"), this);
    lab->setObjectName(QStringLiteral("lab"));
    mainLayout->addWidget(lab);

    mListWidget->setObjectName(QStringLiteral("listwidget"));
    mainLayout->addWidget(mListWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), "CheckAttachmentDialog");
    group.writeEntry("Size", size());
}

void CheckAttachmentDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "CheckAttachmentDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
