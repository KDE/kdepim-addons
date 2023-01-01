/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalscript.h"
#include "configuredialog/viewerpluginexternalconfiguredialog.h"
#include "viewerpluginexternalscriptinterface.h"
#include <KActionCollection>
#include <KPluginFactory>
#include <QPointer>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginExternalscript, "messageviewer_externalscriptplugin.json")

ViewerPluginExternalscript::ViewerPluginExternalscript(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginExternalscript::createView(QWidget *parent, KActionCollection *ac)
{
    auto view = new MessageViewer::ViewerPluginExternalscriptInterface(ac, parent);
    connect(view, &MessageViewer::ViewerPluginExternalscriptInterface::configChanged, this, &ViewerPluginExternalscript::configChanged);
    return view;
}

QString ViewerPluginExternalscript::viewerPluginName() const
{
    return QStringLiteral("external script");
}

void ViewerPluginExternalscript::showConfigureDialog(QWidget *parent)
{
    QPointer<ViewerPluginExternalConfigureDialog> dlg = new ViewerPluginExternalConfigureDialog(parent);
    if (dlg->exec()) {
        Q_EMIT configChanged();
    }
    delete dlg;
}

bool ViewerPluginExternalscript::hasConfigureDialog() const
{
    return true;
}

#include "viewerpluginexternalscript.moc"
