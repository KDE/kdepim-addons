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

#include "languagetoolplugin.h"
#include "languagetoolinterface.h"
#include "languagetoolconfigdialog.h"
#include "languagetoolmanager.h"
#include <PimCommon/CustomToolsWidgetng>
#include <KLocalizedString>
#include <kpluginfactory.h>

#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(LanguagetoolPlugin, "kmail_languagetoolplugin.json")
LanguagetoolPlugin::LanguagetoolPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::CustomToolsPlugin(parent)
{
}

LanguagetoolPlugin::~LanguagetoolPlugin()
{
}

PimCommon::CustomToolsViewInterface *LanguagetoolPlugin::createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent)
{
    LanguagetoolInterface *view = new LanguagetoolInterface(ac, parent);

    connect(view, &LanguagetoolInterface::toolsWasClosed, parent, &PimCommon::CustomToolsWidgetNg::slotToolsWasClosed);
    connect(view, &LanguagetoolInterface::insertText, parent, &PimCommon::CustomToolsWidgetNg::insertText);
    connect(view, &LanguagetoolInterface::activateView, parent, &PimCommon::CustomToolsWidgetNg::slotActivateView);
    return view;
}

QString LanguagetoolPlugin::customToolName() const
{
    return i18n("Languagetool Plugin");
}

bool LanguagetoolPlugin::hasConfigureDialog() const
{
    return true;
}

void LanguagetoolPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<LanguagetoolConfigDialog> dlg = new LanguagetoolConfigDialog(parent);
    if (dlg->exec()) {
        LanguagetoolManager::self()->loadSettings();
    }
    delete dlg;
}

#include "languagetoolplugin.moc"
