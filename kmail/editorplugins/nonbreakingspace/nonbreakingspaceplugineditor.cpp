/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "nonbreakingspaceplugineditor.h"
#include "nonbreakingspaceplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(NonBreakingSpacePluginEditor, "kmail_nonbreakingspaceeditorplugin.json")

NonBreakingSpacePluginEditor::NonBreakingSpacePluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

NonBreakingSpacePluginEditor::~NonBreakingSpacePluginEditor() = default;

MessageComposer::PluginEditorInterface *NonBreakingSpacePluginEditor::createInterface(QObject *parent)
{
    return new NonBreakingSpacePluginEditorInterface(parent);
}

#include "nonbreakingspaceplugineditor.moc"

#include "moc_nonbreakingspaceplugineditor.cpp"
