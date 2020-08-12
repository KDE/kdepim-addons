/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GOOGLeSHORTURLENGINEPLUGIN_H
#define GOOGLeSHORTURLENGINEPLUGIN_H

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

#endif // GOOGLeSHORTURLENGINEPLUGIN_H
