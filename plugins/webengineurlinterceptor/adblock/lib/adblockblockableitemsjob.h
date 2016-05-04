/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ADBLOCKBLOCKABLEITEMSJOB_H
#define ADBLOCKBLOCKABLEITEMSJOB_H

#include <QObject>
#include <QVector>

class QWebEngineView;

namespace AdBlock
{
struct AdBlockResult;
class AdBlockBlockableItemsJob : public QObject
{
    Q_OBJECT
public:

    enum TypeElement {
        UnKnown = 0,
        Image,
        Script
    };

    explicit AdBlockBlockableItemsJob(QObject *parent = Q_NULLPTR);
    ~AdBlockBlockableItemsJob();

    void setWebEngineView(QWebEngineView *webEngineView);


    QWebEngineView *webEngineView() const;
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
    QWebEngineView *mWebEngineView;
};

struct AdBlockResult
{
    AdBlockResult()
        : type(AdBlockBlockableItemsJob::UnKnown)
    {

    }
    bool operator==(const AdBlockResult &other) const {
        return (src == other.src) && (type == other.type);
    }
    QString src;
    AdBlockBlockableItemsJob::TypeElement type;
};
}
Q_DECLARE_TYPEINFO(AdBlock::AdBlockResult, Q_MOVABLE_TYPE);

#endif // ADBLOCKBLOCKABLEITEMSJOB_H
