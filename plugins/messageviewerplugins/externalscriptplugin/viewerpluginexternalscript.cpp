/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscript.h"
#include "viewerpluginexternalscriptinterface.h"
#include "configuredialog/viewerpluginexternalconfiguredialog.h"
#include <KActionCollection>
#include <QPointer>
#include <KPluginFactory>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginExternalscript, "messageviewer_externalscriptplugin.json")

ViewerPluginExternalscript::ViewerPluginExternalscript(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginExternalscript::createView(QWidget *parent, KActionCollection *ac)
{
    MessageViewer::ViewerPluginInterface *view = new MessageViewer::ViewerPluginExternalscriptInterface(ac, parent);
    return view;
}

QString ViewerPluginExternalscript::viewerPluginName() const
{
    return QStringLiteral("external script");
}

void MessageViewer::ViewerPluginExternalscript::showConfigureDialog(QWidget *parent)
{
    QPointer<ViewerPluginExternalConfigureDialog> dlg = new ViewerPluginExternalConfigureDialog(parent);
    if (dlg->exec()) {
        Q_EMIT configChanged();
    }
    delete dlg;
}

bool MessageViewer::ViewerPluginExternalscript::hasConfigureDialog() const
{
    return true;
}

#include "viewerpluginexternalscript.moc"
