/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "../shorturlengineplugin.h"

#include <QVariant>

class Ur1CaShortUrlEnginePlugin : public ShortUrlEnginePlugin
{
    Q_OBJECT
public:
    explicit Ur1CaShortUrlEnginePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~Ur1CaShortUrlEnginePlugin() override;

    ShortUrlEngineInterface *createInterface(QObject *parent) override;
    QString engineName() const override;
};
