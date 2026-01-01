/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "quicktext_export.h"
#include <MessageComposer/ConvertSnippetVariablesUtil>
#include <QObject>
class QMenu;
namespace MessageComposer
{
class PluginComposerInterface;
class ConvertSnippetVariableMenu;
}
class QUICKTEXT_EXPORT QuickTextMenu : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextMenu(QWidget *parentWidget, QObject *parent = nullptr);
    ~QuickTextMenu() override;
    [[nodiscard]] QMenu *menu() const;

    void setPluginComposerInterface(MessageComposer::PluginComposerInterface *composerInterface);

Q_SIGNALS:
    void insertText(const QString &str);
    void insertVariable(MessageComposer::ConvertSnippetVariablesUtil::VariableType type);

private:
    QUICKTEXT_NO_EXPORT void initializeMenu();
    QWidget *const mParentWidget;
    MessageComposer::ConvertSnippetVariableMenu *mMenu = nullptr;
    MessageComposer::PluginComposerInterface *mComposerInterface = nullptr;
};
