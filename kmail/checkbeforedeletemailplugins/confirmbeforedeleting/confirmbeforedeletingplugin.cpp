/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

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

ConfirmBeforeDeletingPlugin::~ConfirmBeforeDeletingPlugin()
{
}

void ConfirmBeforeDeletingPlugin::showConfigureDialog(QWidget *parent)
{
    ConfirmBeforeDeletingDialog dlg(parent);
    dlg.exec();
}

MessageViewer::MessageViewerCheckBeforeDeletingInterface *ConfirmBeforeDeletingPlugin::createInterface(QObject *parent)
{
    return new ConfirmBeforeDeletingInterface(parent);
}

#include "confirmbeforedeletingplugin.moc"
