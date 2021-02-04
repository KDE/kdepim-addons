/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkbeforesendplugin.h"
#include "checkbeforesendinterface.h"
#include "configurewidget/checkbeforesendconfiguredialog.h"
#include "configurewidget/checkbeforesendconfigurewidget.h"

#include <KPluginFactory>
#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(CheckBeforeSendPlugin, "kmail_checkbeforesendplugin.json")

CheckBeforeSendPlugin::CheckBeforeSendPlugin(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorCheckBeforeSend(parent)
{
}

CheckBeforeSendPlugin::~CheckBeforeSendPlugin()
{
}

MessageComposer::PluginEditorCheckBeforeSendInterface *CheckBeforeSendPlugin::createInterface(QObject *parent)
{
    auto interface = new CheckBeforeSendInterface(parent);
    connect(this, &CheckBeforeSendPlugin::configChanged, interface, &CheckBeforeSendInterface::reloadConfig);
    return interface;
}

bool CheckBeforeSendPlugin::hasConfigureDialog() const
{
    return true;
}

void CheckBeforeSendPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<CheckBeforeSendConfigureDialog> dlg = new CheckBeforeSendConfigureDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "checkbeforesendplugin.moc"
