/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "viewerpluginexternalscriptinfo.h"

#include <QObject>
#include <QVector>

class ViewerPluginExternalScriptManager : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptManager(QObject *parent = nullptr);
    ~ViewerPluginExternalScriptManager() override;
    static ViewerPluginExternalScriptManager *self();

    void readExternalScriptInfo();
    Q_REQUIRED_RESULT QVector<ViewerPluginExternalScriptInfo> scriptInfos() const;

private:
    QVector<ViewerPluginExternalScriptInfo> mScriptInfos;
};
