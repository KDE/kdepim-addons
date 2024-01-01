/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertemailplugineditor.h"
#include "insertemailplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(InsertEmailPluginEditor, "kmail_insertemaileditorplugin.json")

InsertEmailPluginEditor::InsertEmailPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

InsertEmailPluginEditor::~InsertEmailPluginEditor() = default;

MessageComposer::PluginEditorInterface *InsertEmailPluginEditor::createInterface(QObject *parent)
{
    return new InsertEmailPluginEditorInterface(parent);
}

#include "insertemailplugineditor.moc"

#include "moc_insertemailplugineditor.cpp"
