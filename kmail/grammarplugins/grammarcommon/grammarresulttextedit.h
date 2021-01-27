/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMARRESULTTEXTEDIT_H
#define GRAMMARRESULTTEXTEDIT_H

#include "grammarcommon_export.h"
#include "grammarerror.h"
#include <QTextEdit>
namespace MessageComposer
{
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
        ReplaceFormatInfo = QTextFormat::UserProperty + 1,
    };
    void slotOpenGrammarUrlInfo(const QString &url);
    void generalPaletteChanged();
    QColor mTextColor;
    QColor mNegativeTextColor;
};

#endif // GRAMMARRESULTTEXTEDIT_H
