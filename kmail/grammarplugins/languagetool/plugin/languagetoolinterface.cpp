/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "languagetoolinterface.h"
#include "grammalecteresultwidget.h"
#include "languagetoolplugin_debug.h"

#include <KPIMTextEdit/RichTextComposer>

#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>

#include <QHBoxLayout>
#include <QTextBlock>

LanguagetoolInterface::LanguagetoolInterface(KActionCollection *ac, QWidget *parent)
    : MessageComposer::PluginEditorGrammarCustomToolsViewInterface(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    mGrammarResultWidget = new GrammalecteResultWidget(this);
    connect(mGrammarResultWidget, &GrammalecteResultWidget::replaceText, this, &LanguagetoolInterface::slotReplaceText);
    connect(mGrammarResultWidget, &GrammalecteResultWidget::checkAgain, this, &LanguagetoolInterface::checkAgain);

    layout->addWidget(mGrammarResultWidget);
    createAction(ac);
}

LanguagetoolInterface::~LanguagetoolInterface()
{
}

void LanguagetoolInterface::slotReplaceText(const MessageComposer::PluginGrammarAction &act)
{
    if (richTextEditor()) {
        QTextBlock block = richTextEditor()->document()->findBlockByNumber(act.blockId() - 1);
        if (block.isValid()) {
            QTextCursor cur(block);
            const int position = cur.position();
            cur.setPosition(position + act.start());
            cur.setPosition(position + act.end(), QTextCursor::KeepAnchor);
            cur.insertText(act.replacement());
        }
    }
}

void LanguagetoolInterface::slotActivateGrammalecte(bool state)
{
    if (state) {
        mGrammarResultWidget->show();
        checkAgain();
        Q_EMIT activateView(this);
    } else {
        mGrammarResultWidget->hide();
        Q_EMIT activateView(nullptr);
    }
}

KToggleAction *LanguagetoolInterface::action() const
{
    return mAction;
}

void LanguagetoolInterface::createAction(KActionCollection *ac)
{
    mAction = new KToggleAction(i18n("&Check Grammar (LanguageTool)"), this);
    connect(mAction, &KToggleAction::triggered, this, &LanguagetoolInterface::slotActivateGrammalecte);
    if (ac) {
        ac->addAction(QStringLiteral("checkgrammar-languagetool"), mAction);
    }
    mAction->setChecked(false);
}

void LanguagetoolInterface::checkAgain()
{
    if (richTextEditor()) {
        mGrammarResultWidget->setText(richTextEditor()->toPlainText());
        mGrammarResultWidget->checkGrammar();
    } else {
        qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "richtexteditor not setted, it's a bug";
    }
}
