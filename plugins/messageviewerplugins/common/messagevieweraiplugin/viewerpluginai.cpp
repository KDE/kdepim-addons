/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginai.h"
#include "viewerpluginaiinterface.h"
#include <KActionCollection>
#include <KPluginFactory>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginAI, "messageviewer_aiplugin.json")

ViewerPluginAI::ViewerPluginAI(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginAI::createView(QWidget *parent, KActionCollection *ac)
{
    MessageViewer::ViewerPluginInterface *view = new MessageViewer::ViewerPluginAIInterface(ac, parent);
    return view;
}

QString ViewerPluginAI::viewerPluginName() const
{
    return QStringLiteral("translator");
}

void MessageViewer::ViewerPluginAI::showConfigureDialog(QWidget *parent)
{
    /*
    TextTranslator::TranslatorConfigureDialog dialog(parent);
    dialog.exec();
    */
}

bool MessageViewer::ViewerPluginAI::hasConfigureDialog() const
{
    return true;
}

#include "viewerpluginai.moc"

#include "moc_viewerpluginai.cpp"
