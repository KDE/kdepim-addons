/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TRIOPABSHORTURLENGINEPLUGIN_H
#define TRIOPABSHORTURLENGINEPLUGIN_H

#include "../shorturlengineplugin.h"

#include <QVariant>

class TriopAbShortUrlEnginePlugin : public ShortUrlEnginePlugin
{
    Q_OBJECT
public:
    explicit TriopAbShortUrlEnginePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~TriopAbShortUrlEnginePlugin() override;

    ShortUrlEngineInterface *createInterface(QObject *parent) override;
    QString engineName() const override;
};

#endif // TRIOPABSHORTURLENGINEPLUGIN_H
