/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALSCRIPTPARSEARGUMENTTEST_H
#define VIEWERPLUGINEXTERNALSCRIPTPARSEARGUMENTTEST_H

#include <QObject>
#include <KMime/Message>
class ViewerPluginExternalScriptParseArgumentTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptParseArgumentTest(QObject *parent = nullptr);
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
