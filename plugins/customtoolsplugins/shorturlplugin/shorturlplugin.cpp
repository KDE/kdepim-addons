/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "shorturlplugin.h"
#include "shorturlview.h"
#include <KLocalizedString>
#include <kpluginfactory.h>
#include <pimcommon/customtoolswidgetng.h>

using namespace PimCommon;
K_PLUGIN_FACTORY_WITH_JSON(PimCommonShorturlPluginFactory, "pimcommon_shorturlplugin.json", registerPlugin<ShorturlPlugin>();
                           )

ShorturlPlugin::ShorturlPlugin(QObject *parent, const QList<QVariant> &)
    : CustomToolsPlugin(parent)
{
}

ShorturlPlugin::~ShorturlPlugin()
{
}

CustomToolsViewInterface *ShorturlPlugin::createView(KActionCollection *ac, CustomToolsWidgetNg *parent)
{
    ShorturlView *view = new ShorturlView(ac, parent);

    connect(view, &ShorturlView::toolsWasClosed, parent, &CustomToolsWidgetNg::slotToolsWasClosed);
    connect(view, &ShorturlView::insertText, parent, &CustomToolsWidgetNg::insertText);
    connect(view, &ShorturlView::activateView, parent, &CustomToolsWidgetNg::slotActivateView);
    return view;
}

QString ShorturlPlugin::customToolName() const
{
    return i18n("Short URL");
}

#include "shorturlplugin.moc"
