/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockblockableitemsjob.h"
#include <QPointer>
#include <QWebEngineView>
#include <WebEngineViewer/WebEngineManageScript>
#include <WebEngineViewer/WebEngineScript>

using namespace AdBlock;
template<typename Arg, typename R, typename C>
struct InvokeWrapper {
    QPointer<R> receiver;
    void (C::*memberFunction)(Arg);
    void operator()(Arg result)
    {
        if (receiver) {
            (receiver->*memberFunction)(result);
        }
    }
};

template<typename Arg, typename R, typename C>

InvokeWrapper<Arg, R, C> invoke(R *receiver, void (C::*memberFunction)(Arg))
{
    InvokeWrapper<Arg, R, C> wrapper = {receiver, memberFunction};
    return wrapper;
}

AdBlockBlockableItemsJob::AdBlockBlockableItemsJob(QObject *parent)
    : QObject(parent)
{
}

AdBlockBlockableItemsJob::~AdBlockBlockableItemsJob() = default;

void AdBlockBlockableItemsJob::setWebEngineView(QWebEngineView *webEngineView)
{
    mWebEngineView = webEngineView;
}

void AdBlockBlockableItemsJob::searchBlockableItems()
{
    if (mWebEngineView) {
        mWebEngineView->page()->runJavaScript(WebEngineViewer::WebEngineScript::findAllImages(),
                                              WebEngineViewer::WebEngineManageScript::scriptWordId(),
                                              invoke(this, &AdBlockBlockableItemsJob::handleSearchBlockableImageItems));
    } else {
        Q_EMIT searchItemsDone(QVector<AdBlock::AdBlockResult>());
        deleteLater();
    }
}

void AdBlockBlockableItemsJob::handleSearchBlockableImageItems(const QVariant &result)
{
    const QList<QVariant> lst = result.toList();
    const QUrl url = mWebEngineView->url();
    const QString host = url.host();
    for (const QVariant &var : lst) {
        const QMap<QString, QVariant> mapVariant = var.toMap();
        QString src = mapVariant.value(QStringLiteral("src")).toString();
        if (!src.isEmpty()) {
            adaptSource(src, host);
            if (src.isEmpty()) {
                continue;
            }
            AdBlock::AdBlockResult result;
            result.src = src;
            result.type = Image;
            if (!mAdblockResultList.contains(result)) {
                mAdblockResultList.append(result);
            }
        }
    }
    mWebEngineView->page()->runJavaScript(WebEngineViewer::WebEngineScript::findAllScripts(),
                                          WebEngineViewer::WebEngineManageScript::scriptWordId(),
                                          invoke(this, &AdBlockBlockableItemsJob::handleSearchBlockableScriptsItems));
}

QWebEngineView *AdBlockBlockableItemsJob::webEngineView() const
{
    return mWebEngineView;
}

void AdBlockBlockableItemsJob::start()
{
    mAdblockResultList.clear();
    searchBlockableItems();
}

void AdBlockBlockableItemsJob::adaptSource(QString &src, const QString &hostName)
{
    if (src.startsWith(QLatin1String("http://")) || src.startsWith(QLatin1String("https://"))) {
        // Nothing
    } else if (src.startsWith(QLatin1String("//"))) {
        src = QLatin1String("https:") + src;
    } else if (src.startsWith(QLatin1Char('/'))) {
        src = QLatin1String("https://") + hostName + src;
    } else {
        src = QString();
    }
}

void AdBlockBlockableItemsJob::handleSearchBlockableScriptsItems(const QVariant &result)
{
    const QList<QVariant> lst = result.toList();
    const QUrl url = mWebEngineView->url();
    const QString host = url.host();
    for (const QVariant &var : lst) {
        const QMap<QString, QVariant> mapVariant = var.toMap();
        QString src = mapVariant.value(QStringLiteral("src")).toString();
        if (!src.isEmpty()) {
            adaptSource(src, host);
            if (src.isEmpty()) {
                continue;
            }
            AdBlock::AdBlockResult result;
            result.src = src;
            result.type = Script;
            if (!mAdblockResultList.contains(result)) {
                mAdblockResultList.append(result);
            }
        }
    }
    // TODO more check ?
    Q_EMIT searchItemsDone(mAdblockResultList);
    deleteLater();
}
