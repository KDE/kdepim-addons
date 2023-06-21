/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertspecialcharacterplugineditor.h"
#include "insertspecialcharacterplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(InsertSpecialCharacterPluginEditor, "kmail_insertspecialcharactereditorplugin.json")

InsertSpecialCharacterPluginEditor::InsertSpecialCharacterPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

InsertSpecialCharacterPluginEditor::~InsertSpecialCharacterPluginEditor() = default;

MessageComposer::PluginEditorInterface *InsertSpecialCharacterPluginEditor::createInterface(QObject *parent)
{
    auto interface = new InsertSpecialCharacterPluginEditorInterface(parent);
    return interface;
}

#include "insertspecialcharacterplugineditor.moc"

#include "moc_insertspecialcharacterplugineditor.cpp"
