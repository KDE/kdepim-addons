/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/


#ifndef GRAMMALECTEMANAGER_H
#define GRAMMALECTEMANAGER_H

#include <QObject>
#include "libkmailgrammalecte_export.h"
class LIBKMAILGRAMMALECTE_EXPORT GrammalecteManager : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteManager(QObject *parent = nullptr);
    ~GrammalecteManager();

    static GrammalecteManager *self();

    Q_REQUIRED_RESULT QString pythonPath() const;
    Q_REQUIRED_RESULT QString grammalectePath() const;

    void setPythonPath(const QString &pythonPath);
    void setGrammalectePath(const QString &grammalectePath);

    void loadSettings();
private:
    QString mPythonPath;
    QString mGrammalectePath;
};

#endif // GRAMMALECTEMANAGER_H
