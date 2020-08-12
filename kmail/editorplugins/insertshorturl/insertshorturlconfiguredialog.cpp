/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlconfiguredialog.h"
#include "insertshorturlconfigurewidget.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>

InsertShorturlConfigureDialog::InsertShorturlConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mInsertShortUrlWidget = new InsertShorturlConfigureWidget(this);
    mInsertShortUrlWidget->setObjectName(QStringLiteral("insertshorturlwidget"));
    mainLayout->addWidget(mInsertShortUrlWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &InsertShorturlConfigureDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &InsertShorturlConfigureDialog::reject);
    mainLayout->addWidget(buttonBox);
}

InsertShorturlConfigureDialog::~InsertShorturlConfigureDialog()
{
}

void InsertShorturlConfigureDialog::accept()
{
    mInsertShortUrlWidget->writeConfig();
    QDialog::accept();
}
