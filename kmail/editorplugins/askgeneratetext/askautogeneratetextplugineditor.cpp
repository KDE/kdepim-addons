/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "askautogeneratetextplugineditor.h"
#include "askautogeneratetextplugineditorinterface.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AskAutogenerateTextPluginEditor, "kmail_askgeneratetexteditorplugin.json")

AskAutogenerateTextPluginEditor::AskAutogenerateTextPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

AskAutogenerateTextPluginEditor::~AskAutogenerateTextPluginEditor() = default;

bool AskAutogenerateTextPluginEditor::hasPopupMenuSupport() const
{
    return true;
}

MessageComposer::PluginEditorInterface *AskAutogenerateTextPluginEditor::createInterface(QObject *parent)
{
    return new AskAutogenerateTextPluginEditorInterface(parent);
}

#include "askautogeneratetextplugineditor.moc"

#include "moc_askautogeneratetextplugineditor.cpp"
