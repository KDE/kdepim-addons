/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

    QListWidget *mListExternal;
    QPushButton *mAddScript;
    QPushButton *mRemoveScript;
    QPushButton *mModifyScript;
};

#endif // VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H
