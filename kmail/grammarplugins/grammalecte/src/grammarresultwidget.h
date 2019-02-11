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

#ifndef GRAMMARRESULTWIDGET_H
#define GRAMMARRESULTWIDGET_H

#include <QWidget>
#include "libkmailgrammalecte_export.h"
#include "grammalectegrammarerror.h"
namespace MessageComposer {
class PluginGrammarAction;
}
class GrammarResultTextEdit;
class LIBKMAILGRAMMALECTE_EXPORT GrammarResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammarResultWidget(QWidget *parent = nullptr);
    ~GrammarResultWidget();
    void setText(const QString &str);
    void checkGrammar();
    void applyGrammarResult(const QVector<GrammarError> &infos);
Q_SIGNALS:
    void replaceText(const MessageComposer::PluginGrammarAction &act);
    void checkAgain();
private:
    void slotCheckGrammarFinished(const QString &result);
    GrammarResultTextEdit *mResult = nullptr;
};

#endif // GRAMMARRESULTWIDGET_H
