/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "askautogeneratetextplugineditor.h"
#include "askautogeneratetextplugineditorinterface.h"
#include "autogenerateconfigureaskdialog.h"
#include <PimAutoGenerateText/AutogenerateConfigureAskManager>

#include <KPluginFactory>
#include <QPointer>

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

bool AskAutogenerateTextPluginEditor::hasConfigureDialog() const
{
    return true;
}

void AskAutogenerateTextPluginEditor::showConfigureDialog(QWidget *parent)
{
    QPointer<AutogenerateConfigureAskDialog> dialog = new AutogenerateConfigureAskDialog(parent);
    AutogenerateConfigureAskManager *manager = new AutogenerateConfigureAskManager(dialog);
    manager->load();
    dialog->setAskInfos(manager->askInfos());
    if (dialog->exec()) {
        manager->setInfos(dialog->askInfos());
        manager->save();
        Q_EMIT configChanged();
    }
    delete dialog;
}

MessageComposer::PluginEditorInterface *AskAutogenerateTextPluginEditor::createInterface(QObject *parent)
{
    auto interface = new AskAutogenerateTextPluginEditorInterface(parent);
    connect(this, &AskAutogenerateTextPluginEditor::configChanged, interface, &AskAutogenerateTextPluginEditorInterface::slotRefreshMenu);
    return interface;
}

#include "askautogeneratetextplugineditor.moc"
#include "moc_askautogeneratetextplugineditor.cpp"
