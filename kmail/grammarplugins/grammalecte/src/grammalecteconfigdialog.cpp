/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "grammalecteconfigdialog.h"
#include "grammalecteconfigwidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>

GrammalecteConfigDialog::GrammalecteConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Configure Grammalecte"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfigWidget = new GrammalecteConfigWidget(this);
    mConfigWidget->setObjectName(QStringLiteral("configwidget"));
    mainLayout->addWidget(mConfigWidget);

    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &GrammalecteConfigDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &GrammalecteConfigDialog::reject);
}

GrammalecteConfigDialog::~GrammalecteConfigDialog()
{

}


void GrammalecteConfigDialog::loadSettings()
{
    //TODO
}

void GrammalecteConfigDialog::saveSettings()
{
    //TODO
}
