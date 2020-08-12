/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionplugineditor.h"
#include "autocorrectionplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(AutoCorrectionPluginEditor, "kmail_autocorrectioneditorplugin.json")

AutoCorrectionPluginEditor::AutoCorrectionPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

AutoCorrectionPluginEditor::~AutoCorrectionPluginEditor()
{
}

MessageComposer::PluginEditorInterface *AutoCorrectionPluginEditor::createInterface(QObject *parent)
{
    AutoCorrectionPluginEditorInterface *interface = new AutoCorrectionPluginEditorInterface(parent);
    return interface;
}

#include "autocorrectionplugineditor.moc"
