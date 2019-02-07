/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "grammalecteplugin.h"
#include "grammalecteinterface.h"
#include "grammalecteconfigdialog.h"
#include "grammalectemanager.h"
#include <PimCommon/CustomToolsWidgetng>
#include <KLocalizedString>
#include <kpluginfactory.h>

#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(GrammalectePlugin, "kmail_grammalecteplugin.json")
GrammalectePlugin::GrammalectePlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::CustomToolsPlugin(parent)
{
}

GrammalectePlugin::~GrammalectePlugin()
{
}

PimCommon::CustomToolsViewInterface *GrammalectePlugin::createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent)
{
    GrammalecteInterface *view = new GrammalecteInterface(ac, parent);

    connect(view, &GrammalecteInterface::toolsWasClosed, parent, &PimCommon::CustomToolsWidgetNg::slotToolsWasClosed);
    connect(view, &GrammalecteInterface::insertText, parent, &PimCommon::CustomToolsWidgetNg::insertText);
    connect(view, &GrammalecteInterface::activateView, parent, &PimCommon::CustomToolsWidgetNg::slotActivateView);
    return view;
}

QString GrammalectePlugin::customToolName() const
{
    return i18n("Grammalecte Plugin");
}

bool GrammalectePlugin::hasConfigureDialog() const
{
    return true;
}

void GrammalectePlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<GrammalecteConfigDialog> dlg = new GrammalecteConfigDialog(parent);
    if (dlg->exec()) {
        GrammalecteManager::self()->loadSettings();
    }
    delete dlg;
}

#include "grammalecteplugin.moc"
