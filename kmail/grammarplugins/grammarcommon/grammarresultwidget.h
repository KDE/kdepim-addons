/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMARRESULTWIDGET_H
#define GRAMMARRESULTWIDGET_H

#include "grammarcommon_export.h"
#include "grammarerror.h"
#include <QWidget>
namespace MessageComposer
{
class PluginGrammarAction;
}
class GrammarResultTextEdit;
class QHBoxLayout;
class GRAMMARCOMMON_EXPORT GrammarResultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammarResultWidget(QWidget *parent = nullptr);
    ~GrammarResultWidget() override;
    void setText(const QString &str);
    virtual void checkGrammar() = 0;
    void applyGrammarResult(const QVector<GrammarError> &infos);
Q_SIGNALS:
    void replaceText(const MessageComposer::PluginGrammarAction &act);
    void checkAgain();
    void closeChecker();

protected:
    virtual void addExtraWidget();
    GrammarResultTextEdit *mResult = nullptr;
    QHBoxLayout *mExtraWidgetLayout = nullptr;

private:
    Q_DISABLE_COPY(GrammarResultWidget)
};

#endif // GRAMMARRESULTWIDGET_H
