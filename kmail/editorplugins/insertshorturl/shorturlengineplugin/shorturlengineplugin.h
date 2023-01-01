/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "shorturl_export.h"
#include <QObject>
class ShortUrlEnginePluginPrivate;
class ShortUrlEngineInterface;
class SHORTURL_EXPORT ShortUrlEnginePlugin : public QObject
{
    Q_OBJECT
public:
    explicit ShortUrlEnginePlugin(QObject *parent = nullptr);
    ~ShortUrlEnginePlugin() override;
    virtual ShortUrlEngineInterface *createInterface(QObject *parent) = 0;
    virtual QString engineName() const = 0;
    QString pluginName() const;
    void setPluginName(const QString &pluginname);

private:
    QString mName;
};
