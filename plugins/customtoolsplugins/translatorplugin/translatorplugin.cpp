/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorplugin.h"
#include "translatorview.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <PimCommon/CustomToolsWidgetng>
#include <PimCommonTextTranslator/TranslatorConfigureDialog>

K_PLUGIN_CLASS_WITH_JSON(TranslatorPlugin, "pimcommon_translatorplugin.json")
TranslatorPlugin::TranslatorPlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::CustomToolsPlugin(parent)
{
}

TranslatorPlugin::~TranslatorPlugin() = default;

PimCommon::CustomToolsViewInterface *TranslatorPlugin::createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent)
{
    auto view = new TranslatorView(ac, parent);

    connect(view, &TranslatorView::toolsWasClosed, parent, &PimCommon::CustomToolsWidgetNg::slotToolsWasClosed);
    connect(view, &TranslatorView::insertText, parent, &PimCommon::CustomToolsWidgetNg::insertText);
    connect(view, &TranslatorView::activateView, parent, &PimCommon::CustomToolsWidgetNg::slotActivateView);
    return view;
}

QString TranslatorPlugin::customToolName() const
{
    return i18n("Translator");
}

bool TranslatorPlugin::hasConfigureDialog() const
{
    return true;
}

void TranslatorPlugin::showConfigureDialog(QWidget *parent)
{
    PimCommonTextTranslator::TranslatorConfigureDialog dialog(parent);
    dialog.exec();
}

#include "translatorplugin.moc"
