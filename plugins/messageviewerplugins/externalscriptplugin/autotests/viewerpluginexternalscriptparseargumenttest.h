/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#ifndef VIEWERPLUGINEXTERNALSCRIPTPARSEARGUMENTTEST_H
#define VIEWERPLUGINEXTERNALSCRIPTPARSEARGUMENTTEST_H

#include <QObject>
#include <KMime/Message>
class ViewerPluginExternalScriptParseArgumentTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptParseArgumentTest(QObject *parent = Q_NULLPTR);
    ~ViewerPluginExternalScriptParseArgumentTest();

private:
    void initializeMessage(const KMime::Message::Ptr &msg);

private Q_SLOTS:
    void shouldReturnOriginalStringListWhenMessageIsNotSetting();
    void shouldReturnSubject();
    void shouldReturnSameListIfNotTransform();
    void shouldReturnTwiceSubject();
    void shouldReturnTo();
    void shouldReturnEmptyStrWhenArgumentIsNotDefined();
    void shouldReturnBody();
    void shouldReturnBcc();
};

#endif // VIEWERPLUGINEXTERNALSCRIPTPARSEARGUMENTTEST_H
