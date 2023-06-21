/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsplugin.h"
#include "automaticaddcontactsconfiguredialog.h"
#include "automaticaddcontactsinterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AutomaticAddContactsPlugin, "kmail_automaticaddcontactsplugin.json")
AutomaticAddContactsPlugin::AutomaticAddContactsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorCheckBeforeSend(parent)
{
}

AutomaticAddContactsPlugin::~AutomaticAddContactsPlugin() = default;

MessageComposer::PluginEditorCheckBeforeSendInterface *AutomaticAddContactsPlugin::createInterface(QObject *parent)
{
    auto interface = new AutomaticAddContactsInterface(parent);
    connect(this, &AutomaticAddContactsPlugin::configChanged, interface, &AutomaticAddContactsInterface::reloadConfig);
    return interface;
}

bool AutomaticAddContactsPlugin::hasConfigureDialog() const
{
    return true;
}

void AutomaticAddContactsPlugin::showConfigureDialog(QWidget *parent)
{
    AutomaticAddContactsConfigureDialog dlg(parent);
    dlg.exec();
}

#include "automaticaddcontactsplugin.moc"

#include "moc_automaticaddcontactsplugin.cpp"
