/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblocklib_export.h"

#include <QObject>
#include <QVector>

class QWebEngineView;

namespace AdBlock
{
struct AdBlockResult;
class ADBLOCKLIB_EXPORT AdBlockBlockableItemsJob : public QObject
{
    Q_OBJECT
public:
    enum TypeElement {
        UnKnown = 0,
        Image,
        Script,
    };

    explicit AdBlockBlockableItemsJob(QObject *parent = nullptr);
    ~AdBlockBlockableItemsJob() override;

    void setWebEngineView(QWebEngineView *webEngineView);

    Q_REQUIRED_RESULT QWebEngineView *webEngineView() const;
    void start();

Q_SIGNALS:
    void searchItemsDone(const QVector<AdBlock::AdBlockResult> &);

private Q_SLOTS:
    void handleSearchBlockableImageItems(const QVariant &result);
    void handleSearchBlockableScriptsItems(const QVariant &result);

private:
    void searchBlockableItems();
    void adaptSource(QString &src, const QString &hostName);
    QVector<AdBlock::AdBlockResult> mAdblockResultList;
    QWebEngineView *mWebEngineView = nullptr;
};

struct ADBLOCKLIB_EXPORT AdBlockResult {
    AdBlockResult()
        : type(AdBlockBlockableItemsJob::UnKnown)
    {
    }

    bool isValid() const
    {
        return (!src.isEmpty()) && (type != AdBlockBlockableItemsJob::UnKnown);
    }

    bool operator==(const AdBlockResult &other) const
    {
        return (src == other.src) && (type == other.type);
    }

    QString src;
    AdBlockBlockableItemsJob::TypeElement type;
};
}
Q_DECLARE_TYPEINFO(AdBlock::AdBlockResult, Q_MOVABLE_TYPE);
