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
    QList<QCheckBox *> mListOptions;
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
