/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactsplugin.h"
#include "automaticaddcontactsinterface.h"
#include "automaticaddcontactsconfigurewidget.h"
#include "automaticaddcontactsconfiguredialog.h"

#include <QPointer>
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AutomaticAddContactsPlugin, "kmail_automaticaddcontactsplugin.json")
AutomaticAddContactsPlugin::AutomaticAddContactsPlugin(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorCheckBeforeSend(parent)
{
}

AutomaticAddContactsPlugin::~AutomaticAddContactsPlugin()
{
}

MessageComposer::PluginEditorCheckBeforeSendInterface *AutomaticAddContactsPlugin::createInterface(QObject *parent)
{
    AutomaticAddContactsInterface *interface = new AutomaticAddContactsInterface(parent);
    connect(this, &AutomaticAddContactsPlugin::configChanged, interface, &AutomaticAddContactsInterface::reloadConfig);
    return interface;
}

bool AutomaticAddContactsPlugin::hasConfigureDialog() const
{
    return true;
}

void AutomaticAddContactsPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<AutomaticAddContactsConfigureDialog> dlg = new AutomaticAddContactsConfigureDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "automaticaddcontactsplugin.moc"
