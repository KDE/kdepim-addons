/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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
#include <KPluginFactory>

#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(LanguageToolPlugin, "kmail_languagetoolplugin.json")
LanguageToolPlugin::LanguageToolPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::CustomToolsPlugin(parent)
{
}

LanguageToolPlugin::~LanguageToolPlugin()
{
}

PimCommon::CustomToolsViewInterface *LanguageToolPlugin::createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent)
{
    LanguageToolInterface *view = new LanguageToolInterface(ac, parent);

    connect(view, &LanguageToolInterface::toolsWasClosed, parent, &PimCommon::CustomToolsWidgetNg::slotToolsWasClosed);
    connect(view, &LanguageToolInterface::insertText, parent, &PimCommon::CustomToolsWidgetNg::insertText);
    connect(view, &LanguageToolInterface::activateView, parent, &PimCommon::CustomToolsWidgetNg::slotActivateView);
    return view;
}

QString LanguageToolPlugin::customToolName() const
{
    return i18n("LanguageTool Plugin");
}

bool LanguageToolPlugin::hasConfigureDialog() const
{
    return true;
}

void LanguageToolPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<LanguageToolConfigDialog> dlg = new LanguageToolConfigDialog(parent);
    if (dlg->exec()) {
        LanguageToolManager::self()->loadSettings();
    }
    delete dlg;
}

#include "languagetoolplugin.moc"
