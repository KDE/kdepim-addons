/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "viewerpluginexternalscriptinfo.h"

#include <QList>
#include <QObject>

class ViewerPluginExternalScriptManager : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptManager(QObject *parent = nullptr);
    ~ViewerPluginExternalScriptManager() override;
    static ViewerPluginExternalScriptManager *self();

    void readExternalScriptInfo();
    [[nodiscard]] QList<ViewerPluginExternalScriptInfo> scriptInfos() const;

private:
    QList<ViewerPluginExternalScriptInfo> mScriptInfos;
};
