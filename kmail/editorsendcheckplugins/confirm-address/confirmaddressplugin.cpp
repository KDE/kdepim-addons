/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddressplugin.h"
#include "confirmaddressconfiguredialog.h"
#include "confirmaddressconfigurewidget.h"
#include "confirmaddressinterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ConfirmAddressPlugin, "kmail_confirmaddressplugin.json")

ConfirmAddressPlugin::ConfirmAddressPlugin(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorCheckBeforeSend(parent)
{
}

ConfirmAddressPlugin::~ConfirmAddressPlugin() = default;

MessageComposer::PluginEditorCheckBeforeSendInterface *ConfirmAddressPlugin::createInterface(QObject *parent)
{
    auto interface = new ConfirmAddressInterface(parent);
    connect(this, &ConfirmAddressPlugin::configChanged, interface, &ConfirmAddressInterface::reloadConfig);
    connect(interface, &ConfirmAddressInterface::forceReloadConfig, this, &ConfirmAddressPlugin::configChanged);
    return interface;
}

bool ConfirmAddressPlugin::hasConfigureDialog() const
{
    return true;
}

void ConfirmAddressPlugin::showConfigureDialog(QWidget *parent)
{
    ConfirmAddressConfigureDialog dlg(parent);
    dlg.exec();
}

#include "confirmaddressplugin.moc"

#include "moc_confirmaddressplugin.cpp"
