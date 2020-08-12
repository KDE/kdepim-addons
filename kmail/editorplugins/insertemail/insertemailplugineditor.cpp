/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

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

InsertEmailPluginEditor::~InsertEmailPluginEditor()
{
}

MessageComposer::PluginEditorInterface *InsertEmailPluginEditor::createInterface(QObject *parent)
{
    InsertEmailPluginEditorInterface *interface = new InsertEmailPluginEditorInterface(parent);
    return interface;
}

#include "insertemailplugineditor.moc"
