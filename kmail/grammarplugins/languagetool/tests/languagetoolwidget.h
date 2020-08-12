/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLWIDGET_H
#define LANGUAGETOOLWIDGET_H

#include <PluginEditorGrammarCustomToolsViewInterface>
#include <QWidget>
class QNetworkAccessManager;
class LanguageToolResultWidget;
class QTextEdit;
class LanguageToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LanguageToolWidget(QWidget *parent = nullptr);
    ~LanguageToolWidget();

private:
    void slotReplaceText(const MessageComposer::PluginGrammarAction &act);
    void slotCheckGrammar();
    void slotError();
    void slotGetListOfLanguages();
    void slotResultFinished(const QString &result);
    void slotGetLanguagesError();
    void slotGetLanguagesFinished(const QString &result);
    QTextEdit *mInput = nullptr;
    LanguageToolResultWidget *mResultWidget = nullptr;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
};

#endif // LANGUAGETOOLWIDGET_H
