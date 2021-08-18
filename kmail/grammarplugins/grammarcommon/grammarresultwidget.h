/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
    void configure();

protected:
    virtual void addExtraWidget();
    GrammarResultTextEdit *const mResult;
    QHBoxLayout *mExtraWidgetLayout = nullptr;

private:
    Q_DISABLE_COPY(GrammarResultWidget)
};

