/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "rot13job.h"

Rot13Job::Rot13Job(QObject *parent)
    : QObject(parent)
{

}

Rot13Job::~Rot13Job()
{

}

void Rot13Job::setText(const QString &text)
{
    mInitialText = text;
}

QString Rot13Job::rot13() const
{
    if (mInitialText.isEmpty())
        return {};

    QString r(mInitialText);

    const int rLenght(r.length());
    for (int i=0; i<rLenght; ++i) {
        const QChar rChar(r.at(i));
        if ( ( rChar >= QLatin1Char('A') && rChar <= QLatin1Char('M') ) ||
             ( rChar >= QLatin1Char('a') && rChar <= QLatin1Char('m') ) ) {
            r[i] = (char)((int)QChar(r[i]).toLatin1() + 13);
        } else {
            if  ( ( rChar >= QLatin1Char('N') && rChar <= QLatin1Char('Z') ) ||
                  ( rChar >= QLatin1Char('n') && rChar <= QLatin1Char('z') ) ) {
                r[i] = (char)((int)QChar(r[i]).toLatin1() - 13);
            }
        }
    }

    return r;
}
