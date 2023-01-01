/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextplugineditor.h"
#include "quicktextconfiguredialog.h"
#include "quicktextplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(QuickTextPluginEditor, "kmail_quicktextplugin.json")

QuickTextPluginEditor::QuickTextPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

QuickTextPluginEditor::~QuickTextPluginEditor() = default;

MessageComposer::PluginEditorInterface *QuickTextPluginEditor::createInterface(QObject *parent)
{
    auto interface = new QuickTextPluginEditorInterface(parent);
    connect(this, &QuickTextPluginEditor::configChanged, interface, &QuickTextPluginEditorInterface::reloadConfig);
    return interface;
}

bool QuickTextPluginEditor::hasStatusBarSupport() const
{
    return true;
}

bool QuickTextPluginEditor::hasConfigureDialog() const
{
    return true;
}

void QuickTextPluginEditor::showConfigureDialog(QWidget *parent)
{
    QPointer<QuickTextConfigureDialog> dlg = new QuickTextConfigureDialog(parent);
    if (dlg->exec()) {
        Q_EMIT configChanged();
    }
    delete dlg;
}

bool QuickTextPluginEditor::canProcessKeyEvent() const
{
    return true;
}

#include "quicktextplugineditor.moc"
