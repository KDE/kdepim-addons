/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditdialog.h"
#include "viewerpluginexternaleditwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

ViewerPluginExternalEditDialog::ViewerPluginExternalEditDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Add or Modify External Script"));
    auto mainLayout = new QVBoxLayout(this);

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
    readConfig();
}

ViewerPluginExternalEditDialog::~ViewerPluginExternalEditDialog()
{
    saveConfig();
}

void ViewerPluginExternalEditDialog::slotScriptIsValid(bool valid)
{
    mOkButton->setEnabled(valid);
}

void ViewerPluginExternalEditDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ViewerPluginExternalEditDialog");
    const QSize size = group.readEntry("Size", QSize(350, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void ViewerPluginExternalEditDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ViewerPluginExternalEditDialog");
    group.writeEntry("Size", size());
    group.sync();
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
