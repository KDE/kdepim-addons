/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

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
    , mMailMergeWidget(new MailMergeWidget(this))
    , mPreview(new QPushButton(i18nc("@action:button", "Preview"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("@title:window", "Mail Merge"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);

    mMailMergeWidget->setObjectName(QLatin1StringView("mailmergewidget"));
    mainLayout->addWidget(mMailMergeWidget);

    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &MailMergeDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &MailMergeDialog::reject);
    mainLayout->addWidget(buttonBox);

    buttonBox->addButton(mPreview, QDialogButtonBox::ActionRole);
    connect(mPreview, &QPushButton::clicked, this, &MailMergeDialog::slotPreview);
    mainLayout->addStretch();
}

MailMergeDialog::~MailMergeDialog() = default;

void MailMergeDialog::slotPreview()
{
    // TODO show generated email
}

#include "moc_mailmergedialog.cpp"
