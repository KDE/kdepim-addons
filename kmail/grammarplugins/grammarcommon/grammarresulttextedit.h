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

#ifndef GRAMMARRESULTTEXTEDIT_H
#define GRAMMARRESULTTEXTEDIT_H

#include <QTextEdit>
#include "grammarerror.h"
#include "grammarcommon_export.h"
namespace MessageComposer {
class PluginGrammarAction;
}
class GRAMMARCOMMON_EXPORT GrammarResultTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit GrammarResultTextEdit(QWidget *parent = nullptr);
    ~GrammarResultTextEdit() override;

    void applyGrammarResult(const QVector<GrammarError> &infos);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

Q_SIGNALS:
    void replaceText(const MessageComposer::PluginGrammarAction &act);
    void checkAgain();
    void closeChecker();
private:
    Q_DISABLE_COPY(GrammarResultTextEdit)
    void slotReplaceWord(const MessageComposer::PluginGrammarAction &act, const QString &replacementWord);
    enum TextInfo {
        ReplaceFormatInfo = QTextFormat::UserProperty + 1
    };
    void generalPaletteChanged();
    QColor mTextColor;
    QColor mNegativeTextColor;
};

#endif // GRAMMARRESULTTEXTEDIT_H
