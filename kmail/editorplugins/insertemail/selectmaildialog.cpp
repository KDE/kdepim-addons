/*
   Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

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

#include "selectmaildialog.h"
#include "selectmailwidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KSharedConfig>

SelectMailDialog::SelectMailDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mSelectMailWidget = new SelectMailWidget(this);
    mSelectMailWidget->setObjectName(QStringLiteral("selectmailwidget"));
    mainLayout->addWidget(mSelectMailWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
    KConfigGroup grp(KSharedConfig::openConfig(), "SelectMailDialog");
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void SelectMailDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "SelectMailDialog");
    grp.writeEntry("Size", size());
    grp.sync();
}
