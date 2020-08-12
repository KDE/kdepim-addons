/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ISGDSHORTURLENGINEPLUGIN_H
#define ISGDSHORTURLENGINEPLUGIN_H

#include "../shorturlengineplugin.h"

#include <QVariant>

class IsgdShortUrlEnginePlugin : public ShortUrlEnginePlugin
{
    Q_OBJECT
public:
    explicit IsgdShortUrlEnginePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~IsgdShortUrlEnginePlugin() override;

    ShortUrlEngineInterface *createInterface(QObject *parent) override;
    QString engineName() const override;
};

#endif // ISGDSHORTURLENGINEPLUGIN_H
