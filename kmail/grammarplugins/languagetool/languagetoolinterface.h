/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
class KActionCollection;
namespace TextGrammarCheck
{
class LanguageToolResultWidget;
class GrammarAction;
}
class LanguageToolInterface : public MessageComposer::PluginEditorGrammarCustomToolsViewInterface
{
    Q_OBJECT
public:
    explicit LanguageToolInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~LanguageToolInterface() override;

    [[nodiscard]] KToggleAction *action() const override;

private:
    Q_DISABLE_COPY(LanguageToolInterface)
    void slotReplaceText(const TextGrammarCheck::GrammarAction &act);
    void slotActivateGrammalecte(bool state);
    void createAction(KActionCollection *ac);
    void closeChecker();
    [[nodiscard]] bool checkAgain();
    TextGrammarCheck::LanguageToolResultWidget *const mGrammarResultWidget;
    KToggleAction *mAction = nullptr;
};
