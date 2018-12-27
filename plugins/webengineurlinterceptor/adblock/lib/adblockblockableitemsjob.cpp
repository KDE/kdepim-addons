/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#include "adblockblockableitemsjob.h"
#include <WebEngineViewer/WebEngineScript>
#include <WebEngineViewer/WebEngineManageScript>
#include <QWebEngineView>
#include <QPointer>

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

AdBlockBlockableItemsJob::~AdBlockBlockableItemsJob()
{
}

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
        //Nothing
    } else if (src.startsWith(QLatin1String("//"))) {
        src = QStringLiteral("https:") + src;
    } else if (src.startsWith(QLatin1Char('/'))) {
        src = QStringLiteral("https://") + hostName + src;
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
    //TODO more check ?
    Q_EMIT searchItemsDone(mAdblockResultList);
    deleteLater();
}
