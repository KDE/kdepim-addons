/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
class KActionCollection;
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
namespace TextGrammarCheck
{
class GrammalecteResultWidget;
class GrammarAction;
}
#else
namespace PimCommonTextGrammarCheck
{
class GrammalecteResultWidget;
class GrammarAction;
}
#endif
class GrammalecteInterface : public MessageComposer::PluginEditorGrammarCustomToolsViewInterface
{
    Q_OBJECT
public:
    explicit GrammalecteInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~GrammalecteInterface() override;

    Q_REQUIRED_RESULT KToggleAction *action() const override;

private:
    Q_DISABLE_COPY(GrammalecteInterface)
    void slotReplaceText(const PimCommonTextGrammarCheck::GrammarAction &act);
    void slotActivateGrammalecte(bool state);
    void createAction(KActionCollection *ac);
    void checkAgain();
    void closeChecker();
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
    TextGrammarCheck::GrammalecteResultWidget *const mGrammarResultWidget;
#else
    PimCommonTextGrammarCheck::GrammalecteResultWidget *const mGrammarResultWidget;
#endif
    KToggleAction *mAction = nullptr;
};
