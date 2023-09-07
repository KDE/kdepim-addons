/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockfilter.h"
#include "libadblockplugin_export.h"
#include <QList>
#include <QObject>
#include <QWebEngineUrlRequestInfo>

#include <adblock.rs.h>
#include <future>
#include <optional>

class LIBADBLOCKPLUGIN_EXPORT AdblockManager : public QObject
{
    Q_OBJECT
public:
    explicit AdblockManager(QObject *parent = nullptr);
    ~AdblockManager() override;

    static AdblockManager *self();

    Q_REQUIRED_RESULT QList<AdblockFilter> adblockFilterLists() const;
    void setAdblockFilterLists(const QList<AdblockFilter> &newAdblockFilterLists);

    Q_REQUIRED_RESULT bool interceptRequest(const QWebEngineUrlRequestInfo &info);
Q_SIGNALS:
    void enabledChanged(bool enabled);

private:
    void reloadConfig();
    QList<AdblockFilter> mAdblockFilterLists;
};
