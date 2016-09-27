/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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
class ViewerPluginExternalConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalConfigureWidget(QWidget *parent = Q_NULLPTR);
    ~ViewerPluginExternalConfigureWidget();
    void load();
    void save();
    void reset();
private:
    enum ItemScriptInfo {
        FileName = Qt::UserRole + 1,
        ReadOnly = Qt::UserRole + 2,
        CommandName = Qt::UserRole + 3,
        Executable = Qt::UserRole + 4,
        IconName = Qt::UserRole + 5,
    };

    void fillScriptInfo(const QVector<ViewerPluginExternalScriptInfo> &scriptInfos);
    void slotAddScript();
    void slotModifyScript();
    void updateButtons();
    void slotRemoveScript();
    QListWidget *mListExternal;
    QPushButton *mAddScript;
    QPushButton *mRemoveScript;
    QPushButton *mModifyScript;
};

#endif // VIEWERPLUGINEXTERNALCONFIGUREWIDGET_H
