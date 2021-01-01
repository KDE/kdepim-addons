/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GRAMMALECTEINTERFACE_H
#define GRAMMALECTEINTERFACE_H

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
class KActionCollection;
class GrammalecteResultWidget;
class GrammalecteInterface : public MessageComposer::PluginEditorGrammarCustomToolsViewInterface
{
    Q_OBJECT
public:
    explicit GrammalecteInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~GrammalecteInterface() override;

    KToggleAction *action() const override;

private:
    Q_DISABLE_COPY(GrammalecteInterface)
    void slotReplaceText(const MessageComposer::PluginGrammarAction &act);
    void slotActivateGrammalecte(bool state);
    void createAction(KActionCollection *ac);
    void checkAgain();
    void closeChecker();
    GrammalecteResultWidget *mGrammarResultWidget = nullptr;
    KToggleAction *mAction = nullptr;
};

#endif // GRAMMALECTEINTERFACE_H
