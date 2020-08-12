/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H
#define VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H

#include <QWidget>
#include "../viewerpluginexternalscriptsloadjob.h"
class QListWidget;
class QPushButton;
class QListWidgetItem;
class ViewerPluginExternalConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalConfigureWidget(QWidget *parent = nullptr);
    ~ViewerPluginExternalConfigureWidget();
    void load();
    void save();
private:
    void modifyScript(QListWidgetItem *item);
    void fillScriptInfo(const QVector<ViewerPluginExternalScriptInfo> &scriptInfos);
    void slotAddScript();
    void slotModifyScript();
    void updateButtons();
    void slotRemoveScript();
    void slotDoubleClicked(QListWidgetItem *item);
    QStringList mFilesToRemove;

    QListWidget *mListExternal = nullptr;
    QPushButton *mAddScript = nullptr;
    QPushButton *mRemoveScript = nullptr;
    QPushButton *mModifyScript = nullptr;
};

#endif // VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H
