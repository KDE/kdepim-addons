/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolplugin.h"
#include "languagetoolinterface.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <PimCommon/CustomToolsWidgetng>
#include <TextGrammarCheck/LanguageToolConfigDialog>
#include <TextGrammarCheck/LanguageToolManager>

K_PLUGIN_CLASS_WITH_JSON(LanguageToolPlugin, "kmail_languagetoolplugin.json")
LanguageToolPlugin::LanguageToolPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::CustomToolsPlugin(parent)
{
}

LanguageToolPlugin::~LanguageToolPlugin() = default;

PimCommon::CustomToolsViewInterface *LanguageToolPlugin::createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent)
{
    auto view = new LanguageToolInterface(ac, parent);

    connect(view, &LanguageToolInterface::toolsWasClosed, parent, &PimCommon::CustomToolsWidgetNg::slotToolsWasClosed);
    connect(view, &LanguageToolInterface::insertText, parent, &PimCommon::CustomToolsWidgetNg::insertText);
    connect(view, &LanguageToolInterface::activateView, parent, &PimCommon::CustomToolsWidgetNg::slotActivateView);
    connect(view, &LanguageToolInterface::configure, this, &LanguageToolPlugin::showConfigureDialog);
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
    TextGrammarCheck::LanguageToolConfigDialog dlg(parent);
    if (dlg.exec()) {
        TextGrammarCheck::LanguageToolManager::self()->loadSettings();
    }
}

#include "languagetoolplugin.moc"

#include "moc_languagetoolplugin.cpp"
