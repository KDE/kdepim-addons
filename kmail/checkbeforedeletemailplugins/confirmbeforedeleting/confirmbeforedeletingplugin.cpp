/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingplugin.h"
#include "confirmbeforedeletingdialog.h"
#include "confirmbeforedeletinginterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ConfirmBeforeDeletingPlugin, "kmail_confirmbeforedeletingplugin.json")

ConfirmBeforeDeletingPlugin::ConfirmBeforeDeletingPlugin(QObject *parent, const QList<QVariant> &)
    : MessageViewer::MessageViewerCheckBeforeDeletingPlugin(parent)
{
}

ConfirmBeforeDeletingPlugin::~ConfirmBeforeDeletingPlugin() = default;

void ConfirmBeforeDeletingPlugin::showConfigureDialog(QWidget *parent)
{
    ConfirmBeforeDeletingDialog dlg(parent);
    dlg.exec();
}

MessageViewer::MessageViewerCheckBeforeDeletingInterface *ConfirmBeforeDeletingPlugin::createInterface(QObject *parent)
{
    auto interface = new ConfirmBeforeDeletingInterface(parent);
    connect(interface, &ConfirmBeforeDeletingInterface::configure, this, &ConfirmBeforeDeletingPlugin::showConfigureDialog);
    return interface;
}

#include "confirmbeforedeletingplugin.moc"

#include "moc_confirmbeforedeletingplugin.cpp"
