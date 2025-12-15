/*
   SPDX-FileCopyrightText: 2018 Sandro Knauß <sknauss@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KMime/Message>
#include <QString>

void testHeaderFile(const QString &data, const QString &name, const QString &dir = QString());
std::shared_ptr<KMime::Message> readAndParseMail(const QString &mailFile);
