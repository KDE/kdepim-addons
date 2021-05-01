/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmaildialog.h"
#include "selectmailwidget.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace
{
static const char myConfigGroupName[] = "SelectMailDialog";
}
SelectMailDialog::SelectMailDialog(QWidget *parent)
    : QDialog(parent)
    , mSelectMailWidget(new SelectMailWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);

    mSelectMailWidget->setObjectName(QStringLiteral("selectmailwidget"));
    mainLayout->addWidget(mSelectMailWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SelectMailDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SelectMailDialog::reject);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

SelectMailDialog::~SelectMailDialog()
{
    writeConfig();
}

QStringList SelectMailDialog::selectedEmails() const
{
    return mSelectMailWidget->selectedEmails();
}

void SelectMailDialog::accept()
{
    Q_EMIT emailSelected(selectedEmails());
    QDialog::accept();
}

void SelectMailDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), myConfigGroupName);
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void SelectMailDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), myConfigGroupName);
    grp.writeEntry("Size", size());
    grp.sync();
}
