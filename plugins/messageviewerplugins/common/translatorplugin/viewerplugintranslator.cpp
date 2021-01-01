/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugintranslator.h"
#include "viewerplugintranslatorinterface.h"
#include <KActionCollection>
#include <KPluginFactory>

using namespace MessageViewer;
K_PLUGIN_CLASS_WITH_JSON(ViewerPluginTranslator, "messageviewer_translatorplugin.json")

ViewerPluginTranslator::ViewerPluginTranslator(QObject *parent, const QList<QVariant> &)
    : MessageViewer::ViewerPlugin(parent)
{
}

ViewerPluginInterface *ViewerPluginTranslator::createView(QWidget *parent, KActionCollection *ac)
{
    MessageViewer::ViewerPluginInterface *view = new MessageViewer::ViewerPluginTranslatorInterface(ac, parent);
    return view;
}

QString ViewerPluginTranslator::viewerPluginName() const
{
    return QStringLiteral("translator");
}

#include "viewerplugintranslator.moc"
