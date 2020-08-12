/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mailmergedialog.h"
#include "widgets/mailmergewidget.h"

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace MailMerge;
MailMergeDialog::MailMergeDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Mail Merge"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);

    mMailMergeWidget = new MailMergeWidget(this);
    mMailMergeWidget->setObjectName(QStringLiteral("mailmergewidget"));
    mainLayout->addWidget(mMailMergeWidget);

    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &MailMergeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &MailMergeDialog::reject);
    mainLayout->addWidget(buttonBox);
}

MailMergeDialog::~MailMergeDialog()
{
}
