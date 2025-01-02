/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomtextplugineditor.h"
#include "zoomtextplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ZoomTextPluginEditor, "kmail_zoomtexteditorplugin.json")

ZoomTextPluginEditor::ZoomTextPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

ZoomTextPluginEditor::~ZoomTextPluginEditor() = default;

MessageComposer::PluginEditorInterface *ZoomTextPluginEditor::createInterface(QObject *parent)
{
    auto interface = new ZoomTextPluginEditorInterface(parent);
    return interface;
}

bool ZoomTextPluginEditor::hasPopupMenuSupport() const
{
    return true;
}

bool ZoomTextPluginEditor::hasStatusBarSupport() const
{
    return true;
}

#include "zoomtextplugineditor.moc"

#include "moc_zoomtextplugineditor.cpp"
