/*
   Copyright (C) 2018 Sandro Knauß <sknauss@kde.org>

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

#ifndef HEADERSTYLEPLUGINTESTUTILS_H
#define HEADERSTYLEPLUGINTESTUTILS_H

#include <QString>
#include <KMime/Message>

void testHeaderFile(const QString &data, const QString &name);
KMime::Message::Ptr readAndParseMail(const QString &mailFile);

#endif // HEADERSTYLEPLUGINTESTUTILS_H
