/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SHORTURLENGINEPLUGINMANAGER_H
#define SHORTURLENGINEPLUGINMANAGER_H

#include <QObject>
#include "shorturl_export.h"
class ShortUrlEnginePlugin;
class ShortUrlEnginePluginManagerPrivate;
class SHORTURL_EXPORT ShortUrlEnginePluginManager : public QObject
{
    Q_OBJECT
public:
    explicit ShortUrlEnginePluginManager(QObject *parent = nullptr);
    ~ShortUrlEnginePluginManager();

    QVector<ShortUrlEnginePlugin *> pluginsList() const;

    static ShortUrlEnginePluginManager *self();
private:
    ShortUrlEnginePluginManagerPrivate *const d;
};

#endif // SHORTURLENGINEPLUGINMANAGER_H
