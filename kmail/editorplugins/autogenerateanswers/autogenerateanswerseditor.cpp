/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateanswerseditor.h"
#include "autogenerateanswerseditorinterface.h"
#include <KPluginFactory>
#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(AutoGenerateAnswersEditor, "kmail_autogenerateanswerseditorplugin.json")

AutoGenerateAnswersEditor::AutoGenerateAnswersEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

AutoGenerateAnswersEditor::~AutoGenerateAnswersEditor() = default;

bool AutoGenerateAnswersEditor::hasPopupMenuSupport() const
{
    return false;
}

bool AutoGenerateAnswersEditor::hasConfigureDialog() const
{
    return false;
}

MessageComposer::PluginEditorInterface *AutoGenerateAnswersEditor::createInterface(QObject *parent)
{
    return new AutoGenerateAnswersEditorInterface(parent);
}

#include "autogenerateanswerseditor.moc"
#include "moc_autogenerateanswerseditor.cpp"
