/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "../shorturlengineplugin.h"

#include <QVariant>

class GoogleShortUrlEnginePlugin : public ShortUrlEnginePlugin
{
    Q_OBJECT
public:
    explicit GoogleShortUrlEnginePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~GoogleShortUrlEnginePlugin() override;

    ShortUrlEngineInterface *createInterface(QObject *parent) override;
};
