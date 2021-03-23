/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "shorturl_export.h"
#include <QObject>
class ShortUrlEnginePlugin;
class ShortUrlEnginePluginManagerPrivate;
class SHORTURL_EXPORT ShortUrlEnginePluginManager : public QObject
{
    Q_OBJECT
public:
    explicit ShortUrlEnginePluginManager(QObject *parent = nullptr);
    ~ShortUrlEnginePluginManager() override;

    QVector<ShortUrlEnginePlugin *> pluginsList() const;

    static ShortUrlEnginePluginManager *self();

private:
    ShortUrlEnginePluginManagerPrivate *const d;
};

