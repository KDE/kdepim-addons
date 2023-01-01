/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
class KActionCollection;
namespace PimCommonTextGrammarCheck
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

    Q_REQUIRED_RESULT KToggleAction *action() const override;

private:
    Q_DISABLE_COPY(LanguageToolInterface)
    void slotReplaceText(const PimCommonTextGrammarCheck::GrammarAction &act);
    void slotActivateGrammalecte(bool state);
    void createAction(KActionCollection *ac);
    void closeChecker();
    bool checkAgain();
    PimCommonTextGrammarCheck::LanguageToolResultWidget *const mGrammarResultWidget;
    KToggleAction *mAction = nullptr;
};
