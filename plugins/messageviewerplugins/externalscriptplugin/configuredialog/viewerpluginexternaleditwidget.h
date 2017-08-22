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

#ifndef VIEWERPLUGINEXTERNALEDITWIDGET_H
#define VIEWERPLUGINEXTERNALEDITWIDGET_H

#include <QWidget>
#include "../viewerpluginexternalscriptinfo.h"
class QLineEdit;
class KUrlRequester;
class ViewerPluginExternalEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalEditWidget(QWidget *parent = nullptr);
    ~ViewerPluginExternalEditWidget();

    void setScriptInfo(const ViewerPluginExternalScriptInfo &info);
    ViewerPluginExternalScriptInfo scriptInfo() const;

    void save();
    void setExistingsNames(const QStringList &existingsNames);

Q_SIGNALS:
    void scriptIsValid(bool valid);

private:
    void slotInfoChanged();
    ViewerPluginExternalScriptInfo mScriptInfo;
    QStringList mExistingsNames;
    QLineEdit *mName;
    QLineEdit *mDescription;
    QLineEdit *mCommandLine;
    KUrlRequester *mExecutable;
};

#endif // VIEWERPLUGINEXTERNALEDITWIDGET_H
