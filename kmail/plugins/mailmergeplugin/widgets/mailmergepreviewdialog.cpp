/*
  SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergepreviewdialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

MailMergePreviewDialog::MailMergePreviewDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Attachment"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonBox"));

    mainLayout->addWidget(buttonBox);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

MailMergePreviewDialog::~MailMergePreviewDialog() = default;

#include "moc_mailmergepreviewdialog.cpp"
