/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalconfiguredialog.h"
#include "viewerpluginexternalconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>

ViewerPluginExternalConfigureDialog::ViewerPluginExternalConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure \"External Script\" Plugin"));
    initLayout();
    buttonBox()->button(QDialogButtonBox::RestoreDefaults)->hide();
}

ViewerPluginExternalConfigureDialog::~ViewerPluginExternalConfigureDialog() = default;

QWidget *ViewerPluginExternalConfigureDialog::createLayout()
{
    mConfigWidget = new ViewerPluginExternalConfigureWidget(this);
    mConfigWidget->setObjectName(QLatin1StringView("externalconfigwidget"));
    return mConfigWidget;
}

void ViewerPluginExternalConfigureDialog::save()
{
    mConfigWidget->save();
}

void ViewerPluginExternalConfigureDialog::load()
{
    mConfigWidget->load();
}

void ViewerPluginExternalConfigureDialog::help()
{
    showHelp(QStringLiteral("kmail2"), QString());
}

#include "moc_viewerpluginexternalconfiguredialog.cpp"
