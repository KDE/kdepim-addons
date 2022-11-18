/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteplugin.h"
#include "grammalecteinterface.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <PimCommon/CustomToolsWidgetng>
#include <PimCommonTextGrammarCheck/GrammalecteConfigDialog>
#include <PimCommonTextGrammarCheck/GrammalecteManager>

#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(GrammalectePlugin, "kmail_grammalecteplugin.json")
GrammalectePlugin::GrammalectePlugin(QObject *parent, const QList<QVariant> &)
    : PimCommon::CustomToolsPlugin(parent)
{
}

GrammalectePlugin::~GrammalectePlugin() = default;

PimCommon::CustomToolsViewInterface *GrammalectePlugin::createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent)
{
    auto view = new GrammalecteInterface(ac, parent);

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
    QPointer<PimCommonTextGrammarCheck::GrammalecteConfigDialog> dlg = new PimCommonTextGrammarCheck::GrammalecteConfigDialog(parent);
    if (dlg->exec()) {
        PimCommonTextGrammarCheck::GrammalecteManager::self()->loadSettings();
    }
    delete dlg;
}

#include "grammalecteplugin.moc"
