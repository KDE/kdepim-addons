/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "grammalecteplugin_debug.h"
#include <KPIMTextEdit/RichTextComposer>

#include <TextGrammarCheck/GrammalecteResultWidget>
#include <TextGrammarCheck/GrammarAction>

#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>

#include <QHBoxLayout>
#include <QTextBlock>

GrammalecteInterface::GrammalecteInterface(KActionCollection *ac, QWidget *parent)
    : MessageComposer::PluginEditorGrammarCustomToolsViewInterface(parent)
    , mGrammarResultWidget(new TextGrammarCheck::GrammalecteResultWidget(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});
    connect(mGrammarResultWidget, &TextGrammarCheck::GrammalecteResultWidget::replaceText, this, &GrammalecteInterface::slotReplaceText);
    connect(mGrammarResultWidget, &TextGrammarCheck::GrammalecteResultWidget::checkAgain, this, &GrammalecteInterface::checkAgain);
    connect(mGrammarResultWidget, &TextGrammarCheck::GrammalecteResultWidget::closeChecker, this, &GrammalecteInterface::closeChecker);
    connect(mGrammarResultWidget, &TextGrammarCheck::GrammalecteResultWidget::configure, this, [this]() {
        Q_EMIT configure(parentWidget());
    });

    layout->addWidget(mGrammarResultWidget);
    createAction(ac);
}

GrammalecteInterface::~GrammalecteInterface() = default;

void GrammalecteInterface::slotReplaceText(const TextGrammarCheck::GrammarAction &act)
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
        ac->addAction(u"checkgrammar-grammalecte"_s, mAction);
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

#include "moc_grammalecteinterface.cpp"
