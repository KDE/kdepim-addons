/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmanager.h"
#include "adblockfilter.h"
#include "globalsettings_webengineurlinterceptoradblock.h"

#include <QFile>

AdblockManager::AdblockManager(QObject *parent)
    : QObject{parent} // parsing the block lists takes some time, try to do it asynchronously
                      // if it is not ready when it's needed, reading the future will block
    , mAdblockInitFuture(std::async(std::launch::async,
                                    [this] {
                                        return createOrRestoreAdblock();
                                    }))
    , mAdblock(std::nullopt)
{
    reloadConfig();
}

AdblockManager::~AdblockManager() = default;

rust::Box<Adblock> AdblockManager::createOrRestoreAdblock()
{
    rust::Box<Adblock> adb = [] {
#if 0
        auto cacheLocation = adblockCacheLocation();
        if (QFile::exists(cacheLocation)) {
            return loadAdblock(cacheLocation.toStdString());
        }
        return newAdblock(AdblockFilterListsManager::filterListPath().toStdString());
#endif
        return newAdblock("");
    }();

    // Q_EMIT adblockInitialized();
    return adb;
}

AdblockManager *AdblockManager::self()
{
    static AdblockManager s_self;
    return &s_self;
}

void AdblockManager::reloadConfig()
{
    // loadSubscriptions();
    const bool enabled = AdBlockSettings::self()->adBlockEnabled();
    Q_EMIT enabledChanged(enabled);
}

QList<AdblockFilter> AdblockManager::adblockFilterLists() const
{
    return mAdblockFilterLists;
}

void AdblockManager::setAdblockFilterLists(const QList<AdblockFilter> &newAdblockFilterLists)
{
    mAdblockFilterLists = newAdblockFilterLists;
}

inline auto resourceTypeToString(const QWebEngineUrlRequestInfo::ResourceType type)
{
    // Strings from https://docs.rs/crate/adblock/0.3.3/source/src/request.rs
    using Type = QWebEngineUrlRequestInfo::ResourceType;
    switch (type) {
    case Type::ResourceTypeMainFrame:
        return "main_frame";
    case Type::ResourceTypeSubFrame:
        return "sub_frame";
    case Type::ResourceTypeStylesheet:
        return "stylesheet";
    case Type::ResourceTypeScript:
        return "script";
    case Type::ResourceTypeFontResource:
        return "font";
    case Type::ResourceTypeImage:
        return "image";
    case Type::ResourceTypeSubResource:
        return "object_subrequest"; // TODO CHECK
    case Type::ResourceTypeObject:
        return "object";
    case Type::ResourceTypeMedia:
        return "media";
    case Type::ResourceTypeFavicon:
        return "image"; // almost
    case Type::ResourceTypeXhr:
        return "xhr";
    case Type::ResourceTypePing:
        return "ping";
    case Type::ResourceTypeCspReport:
        return "csp_report";
    default:
        return "other";
    }
}
bool AdblockManager::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    // Only wait for the adblock initialization if it isn't ready on first use
    if (!mAdblock) {
        qDebug() << "Adblock not yet initialized, blindly allowing request";
        return false;
    }

    const std::string url = info.requestUrl().toString().toStdString();
    const std::string firstPartyUrl = info.firstPartyUrl().toString().toStdString();
    const AdblockResult result = (*mAdblock)->shouldBlock(url, firstPartyUrl, resourceTypeToString(info.resourceType()));

    const auto &redirect = result.redirect;
    const auto &rewrittenUrl = result.rewrittenUrl;
    if (!redirect.empty()) {
        info.redirect(QUrl(QString::fromStdString(std::string(redirect))));
    } else if (result.matched) {
        info.block(result.matched);
    } else if (!rewrittenUrl.empty()) {
        info.redirect(QUrl(QString::fromStdString(std::string(rewrittenUrl))));
    }
    return true;
}

void q_cdebug_adblock(const char *message)
{
    // TODO
    // qCDebug(AdblockCategory) << message;
}
#include "moc_adblockmanager.cpp"
