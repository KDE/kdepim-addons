/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternaleditdialog.h"
#include "viewerpluginexternaleditwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myViewerPluginExternalEditDialog[] = "ViewerPluginExternalEditDialog";
}
ViewerPluginExternalEditDialog::ViewerPluginExternalEditDialog(QWidget *parent)
    : QDialog(parent)
    , mEditWidget(new ViewerPluginExternalEditWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add or Modify External Script"));
    auto mainLayout = new QVBoxLayout(this);

    mEditWidget->setObjectName(QStringLiteral("editwidget"));
    mainLayout->addWidget(mEditWidget);
    connect(mEditWidget, &ViewerPluginExternalEditWidget::scriptIsValid, this, &ViewerPluginExternalEditDialog::slotScriptIsValid);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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

void ViewerPluginExternalEditDialog::saveConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myViewerPluginExternalEditDialog));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

void ViewerPluginExternalEditDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(350, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myViewerPluginExternalEditDialog));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
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

#include "moc_viewerpluginexternaleditdialog.cpp"
