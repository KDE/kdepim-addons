/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTECONFIGWIDGET_H
#define GRAMMALECTECONFIGWIDGET_H

#include <QWidget>
#include "libkmailgrammalecte_export.h"
#include "grammalectegenerateconfigoptionjob.h"
class QCheckBox;
class KUrlRequester;
class QStackedWidget;
class QScrollArea;
class LIBKMAILGRAMMALECTE_EXPORT GrammalecteConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrammalecteConfigWidget(QWidget *parent = nullptr, bool disableMessageBox = false);
    ~GrammalecteConfigWidget();
    void loadSettings();
    void saveSettings();
private:
    Q_DISABLE_COPY(GrammalecteConfigWidget)
    void loadGrammarSettings();
    void slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result);
    void slotGetSettingsError();

    QStringList mSaveOptions;
    QVector<QCheckBox *> mListOptions;
    QWidget *addGeneralTab();
    QWidget *addGrammarTab();
    QStackedWidget *mStackedWidget = nullptr;
    QWidget *mGrammarTabWidget = nullptr;
    QWidget *mReloadSettingsWidget = nullptr;
    QScrollArea *mScrollArea = nullptr;
    KUrlRequester *mPythonPath = nullptr;
    KUrlRequester *mGrammalectePath = nullptr;
    bool mDisableDialogBox = false;
};

#endif // GRAMMALECTECONFIGWIDGET_H
