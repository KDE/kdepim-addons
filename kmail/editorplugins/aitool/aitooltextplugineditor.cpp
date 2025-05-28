/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "aitooltextplugineditor.h"
#include "aitooltextplugineditorinterface.h"
#include <KPluginFactory>
#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(AIToolTextPluginEditor, "kmail_aitooleditorplugin.json")

AIToolTextPluginEditor::AIToolTextPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

AIToolTextPluginEditor::~AIToolTextPluginEditor() = default;

bool AIToolTextPluginEditor::hasPopupMenuSupport() const
{
    return false;
}

bool AIToolTextPluginEditor::hasConfigureDialog() const
{
    return false;
}

MessageComposer::PluginEditorInterface *AIToolTextPluginEditor::createInterface(QObject *parent)
{
    auto interface = new AIToolTextPluginEditorInterface(parent);
    return interface;
}

#include "aitooltextplugineditor.moc"
#include "moc_aitooltextplugineditor.cpp"
