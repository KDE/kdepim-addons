/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTEWIDGET_H
#define GRAMMALECTEWIDGET_H

#include <PluginEditorGrammarCustomToolsViewInterface>
#include <QWidget>
#include "grammalectegenerateconfigoptionjob.h"
class GrammalecteResultWidget;
class QTextEdit;
class GrammalecteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammalecteWidget(QWidget *parent = nullptr);
    ~GrammalecteWidget();

private:
    void slotReplaceText(const MessageComposer::PluginGrammarAction &act);
    void slotCheckGrammar();
    void slotGetSettings();
    void slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result);
    void slotResultFinished(const QString &result);
    QTextEdit *mInput = nullptr;
    GrammalecteResultWidget *mResultWidget = nullptr;
};

#endif // GRAMMALECTEWIDGET_H
