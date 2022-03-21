/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
#include <QWidget>
class QNetworkAccessManager;
class LanguageToolResultWidget;
class QTextEdit;
class LanguageToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LanguageToolWidget(QWidget *parent = nullptr);
    ~LanguageToolWidget() override;

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
