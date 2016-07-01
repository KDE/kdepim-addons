/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *lab = new QLabel(i18n("Do you want to send some attachment?"), this);
    lab->setObjectName(QStringLiteral("lab"));
    mainLayout->addWidget(lab);

    mListWidget = new QListWidget(this);
    mListWidget->setObjectName(QStringLiteral("listwidget"));
    mainLayout->addWidget(mListWidget);

    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, this);
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
