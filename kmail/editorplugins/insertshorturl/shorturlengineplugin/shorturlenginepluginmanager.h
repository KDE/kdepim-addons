/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "shorturl_export.h"
#include <QObject>

#include <memory>

class ShortUrlEnginePlugin;
class ShortUrlEnginePluginManagerPrivate;
class SHORTURL_EXPORT ShortUrlEnginePluginManager : public QObject
{
    Q_OBJECT
public:
    explicit ShortUrlEnginePluginManager(QObject *parent = nullptr);
    ~ShortUrlEnginePluginManager() override;

    [[nodiscard]] QList<ShortUrlEnginePlugin *> pluginsList() const;

    static ShortUrlEnginePluginManager *self();

private:
    std::unique_ptr<ShortUrlEnginePluginManagerPrivate> const d;
};
