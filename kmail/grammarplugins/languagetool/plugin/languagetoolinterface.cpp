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
#include "languagetoolresultwidget.h"
#include "languagetoolplugin_debug.h"
#include "languagetoolmanager.h"
#include <KPIMTextEdit/RichTextComposer>
#include <KMessageBox>

#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>

#include <QHBoxLayout>
#include <QTextBlock>

LanguageToolInterface::LanguageToolInterface(KActionCollection *ac, QWidget *parent)
    : MessageComposer::PluginEditorGrammarCustomToolsViewInterface(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    mGrammarResultWidget = new LanguageToolResultWidget(this);
    connect(mGrammarResultWidget, &LanguageToolResultWidget::replaceText, this, &LanguageToolInterface::slotReplaceText);
    connect(mGrammarResultWidget, &LanguageToolResultWidget::checkAgain, this, &LanguageToolInterface::checkAgain);

    layout->addWidget(mGrammarResultWidget);
    createAction(ac);
}

LanguageToolInterface::~LanguageToolInterface()
{
}

void LanguageToolInterface::slotReplaceText(const MessageComposer::PluginGrammarAction &act)
{
    if (richTextEditor()) {
        QTextBlock block = richTextEditor()->document()->findBlockByNumber(act.blockId() - 1);
        if (block.isValid()) {
            QTextCursor cur(block);
            const int position = cur.position()+ act.start();
            cur.setPosition(position);
            cur.setPosition(position + act.length(), QTextCursor::KeepAnchor);
            cur.insertText(act.replacement());
        }
    }
}

void LanguageToolInterface::slotActivateGrammalecte(bool state)
{
    if (state) {
        if (!checkAgain()) {
            mAction->setChecked(false);
            return;
        }
        mGrammarResultWidget->show();
        Q_EMIT activateView(this);
    } else {
        mGrammarResultWidget->hide();
        Q_EMIT activateView(nullptr);
    }
}

KToggleAction *LanguageToolInterface::action() const
{
    return mAction;
}

void LanguageToolInterface::createAction(KActionCollection *ac)
{
    mAction = new KToggleAction(i18n("&Check Grammar (LanguageTool)"), this);
    connect(mAction, &KToggleAction::triggered, this, &LanguageToolInterface::slotActivateGrammalecte);
    if (ac) {
        ac->addAction(QStringLiteral("checkgrammar-languagetool"), mAction);
    }
    mAction->setChecked(false);
}

bool LanguageToolInterface::checkAgain()
{
    if (richTextEditor()) {
        if (!LanguageToolManager::self()->useLocalInstance()) {
            if (KMessageBox::warningYesNo(parentWidget(), i18n("You do not use local instance. Your text will send on a external web site (https://languagetool.org/). Do you want to continue?"),
                                          i18n("Check Grammar with LanguageTool"),
                                          KStandardGuiItem::yes(),
                                          KStandardGuiItem::no(),
                                          QStringLiteral("send_data_on_languagetool")) == KMessageBox::No) {
                return false;
            }
        }
        mGrammarResultWidget->setText(richTextEditor()->toPlainText());
        mGrammarResultWidget->checkGrammar();
    } else {
        qCWarning(KMAIL_EDITOR_LANGUAGETOOL_PLUGIN_LOG) << "richtexteditor not setted, it's a bug";
    }
    return true;
}
