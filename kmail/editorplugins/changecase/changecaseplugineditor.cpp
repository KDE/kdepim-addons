/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "changecaseplugineditor.h"
#include "changecaseplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ChangeCasePluginEditor, "kmail_changecaseeditorplugin.json")

ChangeCasePluginEditor::ChangeCasePluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

ChangeCasePluginEditor::~ChangeCasePluginEditor()
{
}

bool ChangeCasePluginEditor::hasPopupMenuSupport() const
{
    return true;
}

MessageComposer::PluginEditorInterface *ChangeCasePluginEditor::createInterface(QObject *parent)
{
    ChangeCasePluginEditorInterface *interface = new ChangeCasePluginEditorInterface(parent);
    return interface;
}

#include "changecaseplugineditor.moc"
