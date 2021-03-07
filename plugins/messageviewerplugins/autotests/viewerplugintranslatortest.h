/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINTRANSLATORTEST_H
#define VIEWERPLUGINTRANSLATORTEST_H

#include <QObject>

class ViewerPluginTranslatorTest : public QObject
{
    Q_OBJECT
public:
    explicit ViewerPluginTranslatorTest(QObject *parent = nullptr);
    ~ViewerPluginTranslatorTest() override;

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldCreateAction();
};

#endif // VIEWERPLUGINTRANSLATORTEST_H
