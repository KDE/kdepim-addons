/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "../shorturlengineplugin.h"

#include <QVariant>

class IsgdShortUrlEnginePlugin : public ShortUrlEnginePlugin
{
    Q_OBJECT
public:
    explicit IsgdShortUrlEnginePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~IsgdShortUrlEnginePlugin() override;

    [[nodiscard]] ShortUrlEngineInterface *createInterface(QObject *parent) override;
    [[nodiscard]] QString engineName() const override;
};
