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

    Q_REQUIRED_RESULT bool interceptRequest(QWebEngineUrlRequestInfo &info);
Q_SIGNALS:
    void enabledChanged(bool enabled);
    void adblockInitialized();

private:
    void reloadConfig();
    Q_REQUIRED_RESULT QString adblockCacheLocation() const;

    /// If an adblock cache is found, loads it, otherwise creates a new adblock
    /// from the current filter lists.
    rust::Box<Adblock> createOrRestoreAdblock();

    std::future<rust::Box<Adblock>> mAdblockInitFuture;
    std::optional<rust::Box<Adblock>> mAdblock;
    QList<AdblockFilter> mAdblockFilterLists;
};

extern "C" {
void q_cdebug_adblock(const char *message);
}
