/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

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

AutoCorrectionPluginEditor::~AutoCorrectionPluginEditor() = default;

MessageComposer::PluginEditorInterface *AutoCorrectionPluginEditor::createInterface(QObject *parent)
{
    return new AutoCorrectionPluginEditorInterface(parent);
}

#include "autocorrectionplugineditor.moc"
