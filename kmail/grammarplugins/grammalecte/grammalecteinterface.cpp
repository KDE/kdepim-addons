/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteinterface.h"
#include "grammalecteplugin_debug.h"
#include <KPIMTextEdit/RichTextComposer>
#include <PimCommonTextGrammarCheck/GrammalecteResultWidget>
#include <PimCommonTextGrammarCheck/GrammarAction>

#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>

#include <QHBoxLayout>
#include <QTextBlock>

GrammalecteInterface::GrammalecteInterface(KActionCollection *ac, QWidget *parent)
    : MessageComposer::PluginEditorGrammarCustomToolsViewInterface(parent)
    , mGrammarResultWidget(new PimCommonTextGrammarCheck::GrammalecteResultWidget(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});
    connect(mGrammarResultWidget, &PimCommonTextGrammarCheck::GrammalecteResultWidget::replaceText, this, &GrammalecteInterface::slotReplaceText);
    connect(mGrammarResultWidget, &PimCommonTextGrammarCheck::GrammalecteResultWidget::checkAgain, this, &GrammalecteInterface::checkAgain);
    connect(mGrammarResultWidget, &PimCommonTextGrammarCheck::GrammalecteResultWidget::closeChecker, this, &GrammalecteInterface::closeChecker);
    connect(mGrammarResultWidget, &PimCommonTextGrammarCheck::GrammalecteResultWidget::configure, this, [this]() {
        Q_EMIT configure(parentWidget());
    });

    layout->addWidget(mGrammarResultWidget);
    createAction(ac);
}

GrammalecteInterface::~GrammalecteInterface() = default;

void GrammalecteInterface::slotReplaceText(const PimCommonTextGrammarCheck::GrammarAction &act)
{
    if (richTextEditor()) {
        QTextBlock block = richTextEditor()->document()->findBlockByNumber(act.blockId() - 1);
        if (block.isValid()) {
            QTextCursor cur(block);
            const int position = cur.position() + act.start();
            cur.setPosition(position);
            cur.setPosition(position + act.length(), QTextCursor::KeepAnchor);
            cur.insertText(act.replacement());
        }
    }
}

void GrammalecteInterface::slotActivateGrammalecte(bool state)
{
    if (state) {
        mGrammarResultWidget->show();
        checkAgain();
        Q_EMIT activateView(this);
    } else {
        closeChecker();
    }
}

void GrammalecteInterface::closeChecker()
{
    mGrammarResultWidget->hide();
    Q_EMIT activateView(nullptr);
}

KToggleAction *GrammalecteInterface::action() const
{
    return mAction;
}

void GrammalecteInterface::createAction(KActionCollection *ac)
{
    mAction = new KToggleAction(i18n("&Check Grammar (Grammalecte)"), this);
    connect(mAction, &KToggleAction::triggered, this, &GrammalecteInterface::slotActivateGrammalecte);
    if (ac) {
        ac->addAction(QStringLiteral("checkgrammar-grammalecte"), mAction);
    }
    mAction->setChecked(false);
}

void GrammalecteInterface::checkAgain()
{
    if (richTextEditor()) {
        mGrammarResultWidget->setText(richTextEditor()->toPlainText());
        mGrammarResultWidget->checkGrammar();
    } else {
        qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "richtexteditor not set, it's a bug";
    }
}
