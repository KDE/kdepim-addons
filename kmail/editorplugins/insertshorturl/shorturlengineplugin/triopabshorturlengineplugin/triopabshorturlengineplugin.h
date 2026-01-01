/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "../shorturlengineplugin.h"

#include <QVariant>

class TriopAbShortUrlEnginePlugin : public ShortUrlEnginePlugin
{
    Q_OBJECT
public:
    explicit TriopAbShortUrlEnginePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~TriopAbShortUrlEnginePlugin() override;

    [[nodiscard]] ShortUrlEngineInterface *createInterface(QObject *parent) override;
    [[nodiscard]] QString engineName() const override;
};
