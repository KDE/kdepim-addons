/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H
#define VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H

#include "../viewerpluginexternalscriptsloadjob.h"
#include <QWidget>
class QListWidget;
class QPushButton;
class QListWidgetItem;
class ViewerPluginExternalConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalConfigureWidget(QWidget *parent = nullptr);
    ~ViewerPluginExternalConfigureWidget() override;
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

    QListWidget *const mListExternal;
    QPushButton *const mAddScript;
    QPushButton *const mRemoveScript;
    QPushButton *const mModifyScript;
};

#endif // VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H
