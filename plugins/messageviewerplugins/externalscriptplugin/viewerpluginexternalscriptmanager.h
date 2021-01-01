/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALSCRIPTMANAGER_H
#define VIEWERPLUGINEXTERNALSCRIPTMANAGER_H

#include "viewerpluginexternalscriptinfo.h"

#include <QObject>
#include <QVector>

class ViewerPluginExternalScriptManager : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptManager(QObject *parent = nullptr);
    ~ViewerPluginExternalScriptManager();
    static ViewerPluginExternalScriptManager *self();

    void readExternalScriptInfo();
    QVector<ViewerPluginExternalScriptInfo> scriptInfos() const;

private:
    QVector<ViewerPluginExternalScriptInfo> mScriptInfos;
};

#endif // VIEWERPLUGINEXTERNALSCRIPTMANAGER_H
