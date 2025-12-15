/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KMime/Message>
#include <QObject>
class ViewerPluginExternalScriptParseArgumentTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalScriptParseArgumentTest(QObject *parent = nullptr);
    ~ViewerPluginExternalScriptParseArgumentTest() override;

private:
    void initializeMessage(const std::shared_ptr<KMime::Message> &msg);

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
