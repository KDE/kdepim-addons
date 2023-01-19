/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
class KActionCollection;
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
namespace TextGrammarCheck
#else
namespace PimCommonTextGrammarCheck
#endif
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
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
    void slotReplaceText(const TextGrammarCheck::GrammarAction &act);
#else
    void slotReplaceText(const PimCommonTextGrammarCheck::GrammarAction &act);
#endif
    void slotActivateGrammalecte(bool state);
    void createAction(KActionCollection *ac);
    void closeChecker();
    bool checkAgain();
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
    TextGrammarCheck::LanguageToolResultWidget *const mGrammarResultWidget;
#else
    PimCommonTextGrammarCheck::LanguageToolResultWidget *const mGrammarResultWidget;
#endif
    KToggleAction *mAction = nullptr;
};
