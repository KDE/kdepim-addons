/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockfilter.h"
#include "libadblockplugin_export.h"
#include <QList>
#include <QNetworkAccessManager>
#include <QObject>
#include <QWebEngineUrlRequestInfo>

#include <adblock.rs.h>
#include <future>
#include <optional>

class AdblockListsManager;
class QNetworkReply;

class LIBADBLOCKPLUGIN_EXPORT AdblockManager : public QObject
{
    Q_OBJECT
public:
    explicit AdblockManager(QObject *parent = nullptr);
    ~AdblockManager() override;

    static AdblockManager *self();

    [[nodiscard]] QList<AdblockFilter> adblockFilterLists() const;
    void setAdblockFilterLists(const QList<AdblockFilter> &newAdblockFilterLists);

    [[nodiscard]] bool interceptRequest(QWebEngineUrlRequestInfo &info);

    void refreshLists();

    [[nodiscard]] QString filterListIdFromUrl(const QString &url) const;
    [[nodiscard]] QString adblockListText(const QString &url);

Q_SIGNALS:
    void enabledChanged(bool enabled);
    void adblockInitialized();
    void refreshFinished();

private Q_SLOTS:
    void handleListFetched(QNetworkReply *reply);

private:
    LIBADBLOCKPLUGIN_NO_EXPORT void reloadConfig();
    LIBADBLOCKPLUGIN_NO_EXPORT void writeConfig();
    [[nodiscard]] LIBADBLOCKPLUGIN_NO_EXPORT QString adblockCacheLocation() const;

    /// If an adblock cache is found, loads it, otherwise creates a new adblock
    /// from the current filter lists.
    LIBADBLOCKPLUGIN_NO_EXPORT rust::Box<Adblock> createOrRestoreAdblock();

    AdblockListsManager *const mAdblockListManager;
    std::future<rust::Box<Adblock>> mAdblockInitFuture;
    std::optional<rust::Box<Adblock>> mAdblock;
    QList<AdblockFilter> mAdblockFilterLists;
    QNetworkAccessManager m_networkManager;
    int m_runningRequests = 0;
};

extern "C" {
void q_cdebug_adblock(const char *message);
}
