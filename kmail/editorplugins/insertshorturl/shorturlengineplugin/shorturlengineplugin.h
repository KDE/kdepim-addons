/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SHORTURLENGINEPLUGIN_H
#define SHORTURLENGINEPLUGIN_H

#include <QObject>
#include "shorturl_export.h"
class ShortUrlEnginePluginPrivate;
class ShortUrlEngineInterface;
class SHORTURL_EXPORT ShortUrlEnginePlugin : public QObject
{
    Q_OBJECT
public:
    explicit ShortUrlEnginePlugin(QObject *parent = nullptr);
    ~ShortUrlEnginePlugin();
    virtual ShortUrlEngineInterface *createInterface(QObject *parent) = 0;
    virtual QString engineName() const = 0;
    QString pluginName() const;
    void setPluginName(const QString &pluginname);

private:
    QString mName;
};
#endif // SHORTURLENGINEPLUGIN_H
