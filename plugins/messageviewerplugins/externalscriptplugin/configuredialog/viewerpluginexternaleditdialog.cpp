/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "viewerpluginexternaleditdialog.h"
#include "viewerpluginexternaleditwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QPushButton>

ViewerPluginExternalEditDialog::ViewerPluginExternalEditDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Add or Modify External Script"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mEditWidget = new ViewerPluginExternalEditWidget(this);
    mEditWidget->setObjectName(QStringLiteral("editwidget"));
    mainLayout->addWidget(mEditWidget);
    connect(mEditWidget, &ViewerPluginExternalEditWidget::scriptIsValid, this, &ViewerPluginExternalEditDialog::slotScriptIsValid);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ViewerPluginExternalEditDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ViewerPluginExternalEditDialog::reject);
    mainLayout->addWidget(buttonBox);
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    mOkButton->setEnabled(false);
    resize(350, 200);
}

ViewerPluginExternalEditDialog::~ViewerPluginExternalEditDialog()
{

}

void ViewerPluginExternalEditDialog::slotScriptIsValid(bool valid)
{
    mOkButton->setEnabled(valid);
}

void ViewerPluginExternalEditDialog::slotAccepted()
{
    mEditWidget->save();
    accept();
}

void ViewerPluginExternalEditDialog::setExistingsNames(const QStringList &existingsNames)
{
    mEditWidget->setExistingsNames(existingsNames);
}

void ViewerPluginExternalEditDialog::setScriptInfo(const ViewerPluginExternalScriptInfo &info)
{
    mEditWidget->setScriptInfo(info);
}

ViewerPluginExternalScriptInfo ViewerPluginExternalEditDialog::scriptInfo() const
{
    return mEditWidget->scriptInfo();
}
