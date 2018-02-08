/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "viewerpluginexternalscript.h"
#include "viewerpluginexternalscriptinterface.h"
#include "configuredialog/viewerpluginexternalconfiguredialog.h"
#include <KActionCollection>
#include <QPointer>
#include <kpluginfactory.h>
#include "kcoreaddons_kdepim_compat.h"
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
