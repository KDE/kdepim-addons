/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockmanager.h"
#include "adblocklistsmanager.h"

#include "globalsettings_webengineurlinterceptoradblock.h"
#include "libadblockplugin_debug.h"

#include <QDir>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStandardPaths>

[[nodiscard]] QString filterListPath()
{
    static const auto path = []() -> QString {
        QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QStringLiteral("/filterlists/");
        QDir(path).mkpath(QStringLiteral("."));
        return path;
    }();
    return path;
}

AdblockManager::AdblockManager(QObject *parent)
    : QObject{parent} // parsing the block lists takes some time, try to do it asynchronously
                      // if it is not ready when it's needed, reading the future will block
    , mAdblockInitFuture(std::async(std::launch::async,
                                    [this] {
                                        return createOrRestoreAdblock();
                                    }))
    , mAdblock(std::nullopt)
    , mAdblockListManager(new AdblockListsManager(this))
{
    reloadConfig();

    connect(&m_networkManager, &QNetworkAccessManager::finished, this, &AdblockManager::handleListFetched);
    m_networkManager.setRedirectPolicy(QNetworkRequest::SameOriginRedirectPolicy);

    if (QDir(filterListPath()).isEmpty()) {
        refreshLists();
    }
}

AdblockManager::~AdblockManager()
{
    if (mAdblock && (*mAdblock)->isValid() && (*mAdblock)->needsSave()) {
        (*mAdblock)->save(adblockCacheLocation().toStdString());
    }
}

QString AdblockManager::adblockCacheLocation() const
{
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QStringLiteral("/adblockCache");
}

rust::Box<Adblock> AdblockManager::createOrRestoreAdblock()
{
    rust::Box<Adblock> adb = [this] {
        auto cacheLocation = adblockCacheLocation();
        if (QFile::exists(cacheLocation)) {
            return loadAdblock(cacheLocation.toStdString());
        }
        return newAdblock(mAdblockListManager->filterListsPath().toStdString());
    }();

    Q_EMIT adblockInitialized();
    return adb;
}

void copyStream(QIODevice &input, QIODevice &output)
{
    constexpr auto BUFFER_SIZE = 1024;

    QByteArray buffer;
    buffer.reserve(BUFFER_SIZE);

    while (true) {
        int64_t read = input.read(buffer.data(), BUFFER_SIZE);

        if (read > 0) {
            output.write(buffer.data(), read);
        } else {
            break;
        }
    }
}

AdblockManager *AdblockManager::self()
{
    static AdblockManager s_self = AdblockManager();
    return &s_self;
}

void AdblockManager::reloadConfig()
{
    const bool enabled = AdBlockSettings::self()->adBlockEnabled();
    Q_EMIT enabledChanged(enabled);

    mAdblockFilterLists.clear();

    const auto filterUrls = AdBlockSettings::self()->adblockFilterUrls();
    const auto filterNames = AdBlockSettings::self()->adblockFilterNames();

    auto namesIt = filterNames.begin();
    auto urlsIt = filterUrls.begin();

    // Otherwise list is corrupted, but we will still not crash in release mode
    Q_ASSERT(filterNames.size() == filterUrls.size());

    while (namesIt != filterNames.end() && urlsIt != filterUrls.end()) {
        AdblockFilter filter;
        filter.setName(*namesIt);
        filter.setUrl(urlsIt->toDisplayString());

        namesIt++;
        urlsIt++;
        mAdblockFilterLists << filter;
    }
}

void AdblockManager::writeConfig()
{
    QStringList filterNames;
    QList<QUrl> filterUrls;

    for (const auto &filterList : std::as_const(mAdblockFilterLists)) {
        filterNames.push_back(filterList.name());
        filterUrls.push_back(QUrl(filterList.url()));
    }

    AdBlockSettings::self()->setAdblockFilterNames(filterNames);
    AdBlockSettings::self()->setAdblockFilterUrls(filterUrls);
    AdBlockSettings::self()->save();
}

QString AdblockManager::filterListIdFromUrl(const QString &url) const
{
    QCryptographicHash fileNameHash(QCryptographicHash::Sha256);
    fileNameHash.addData(url.toUtf8());
    return QString::fromUtf8(fileNameHash.result().toHex());
}

void AdblockManager::handleListFetched(QNetworkReply *reply)
{
    Q_ASSERT(reply);

    m_runningRequests--;

    if (m_runningRequests < 1) {
        Q_EMIT refreshFinished();
    }

    const auto id = filterListIdFromUrl(reply->url().toString());

    QFile file(filterListPath() + id);
    if (!file.open(QIODevice::WriteOnly)) {
        qCWarning(LIBADBLOCKPLUGIN_PLUGIN_LOG) << "Failed to open" << file.fileName() << "for writing."
                                               << "Filter list not updated";
        return;
    }

    copyStream(*reply, file);
}

void AdblockManager::refreshLists()
{
    // Delete old lists, in case the names change.
    // Otherwise we might not be overwriting all of them.
    const QDir dir(filterListPath());
    const auto entries = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    for (const auto &entry : entries) {
        const QString path{dir.path() + QDir::separator() + entry};
        if (!QFile::remove(path)) {
            qCWarning(LIBADBLOCKPLUGIN_PLUGIN_LOG) << "Impossible to remove file: " << path;
        }
    }

    for (const auto &list : std::as_const(mAdblockFilterLists)) {
        m_runningRequests++;
        m_networkManager.get(QNetworkRequest(QUrl(list.url())));
    }
}

QList<AdblockFilter> AdblockManager::adblockFilterLists() const
{
    return mAdblockFilterLists;
}

void AdblockManager::setAdblockFilterLists(const QList<AdblockFilter> &newAdblockFilterLists)
{
    if (mAdblockFilterLists != newAdblockFilterLists) {
        mAdblockFilterLists = newAdblockFilterLists;
        writeConfig();
    }
}

inline auto resourceTypeToString(const QWebEngineUrlRequestInfo::ResourceType type)
{
    // Strings from https://docs.rs/crate/adblock/0.8.1/source/src/request.rs
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
        qCDebug(LIBADBLOCKPLUGIN_PLUGIN_LOG) << "Adblock not yet initialized, blindly allowing request";
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
    qCDebug(LIBADBLOCKPLUGIN_PLUGIN_LOG) << "AdblockManager message: " << message;
}

#include "moc_adblockmanager.cpp"
