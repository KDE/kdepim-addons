/*
   SPDX-FileCopyrightText: 2018 Sandro Knauß <sknauss@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef HEADERSTYLEPLUGINTESTUTILS_H
#define HEADERSTYLEPLUGINTESTUTILS_H

#include <QString>
#include <KMime/Message>

void testHeaderFile(const QString &data, const QString &name, const QString &dir = QString());
KMime::Message::Ptr readAndParseMail(const QString &mailFile);

#endif // HEADERSTYLEPLUGINTESTUTILS_H
