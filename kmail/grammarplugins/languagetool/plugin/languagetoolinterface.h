/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef LANGUAGETOOLINTERFACE_H
#define LANGUAGETOOLINTERFACE_H

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
class KActionCollection;
class LanguageToolResultWidget;
class LanguageToolInterface : public MessageComposer::PluginEditorGrammarCustomToolsViewInterface
{
    Q_OBJECT
public:
    explicit LanguageToolInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~LanguageToolInterface() override;

    KToggleAction *action() const override;

private:
    Q_DISABLE_COPY(LanguageToolInterface)
    void slotReplaceText(const MessageComposer::PluginGrammarAction &act);
    void slotActivateGrammalecte(bool state);
    void createAction(KActionCollection *ac);
    void closeChecker();
    bool checkAgain();
    LanguageToolResultWidget *mGrammarResultWidget = nullptr;
    KToggleAction *mAction = nullptr;
};

#endif // LANGUAGETOOLINTERFACE_H
