/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#ifndef ADBLOCKMANAGER_H
#define ADBLOCKMANAGER_H

#include <QObject>
#include <QWebEngineUrlRequestInfo>
#include "adblocklib_export.h"
namespace AdBlock
{
class AdBlockMatcher;
class ADBLOCKLIB_EXPORT AdblockManager : public QObject
{
    Q_OBJECT
public:
    static AdblockManager *self();
    explicit AdblockManager(QObject *parent = Q_NULLPTR);
    ~AdblockManager();
    bool isEnabled() const;

    bool interceptRequest(const QWebEngineUrlRequestInfo &info);

Q_SIGNALS:
    void enabledChanged(bool);

public Q_SLOTS:
    void reloadConfig();

private:
    bool canRunOnScheme(const QString &scheme) const;
    bool mEnabled;
    AdBlockMatcher *mAdBlockMatcher;
};
}
#endif // ADBLOCKMANAGER_H
