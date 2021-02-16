/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TEMPLATEPARSEREMAILADDRESSREQUESTERAKONADITEST_H
#define TEMPLATEPARSEREMAILADDRESSREQUESTERAKONADITEST_H

#include <QObject>

class TemplateParserEmailAddressRequesterAkonadiTest : public QObject
{
    Q_OBJECT
public:
    explicit TemplateParserEmailAddressRequesterAkonadiTest(QObject *parent = nullptr);
    ~TemplateParserEmailAddressRequesterAkonadiTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldEmitSignal();
    void shouldClearValue();
    void shouldAssignValue();
};

#endif // TEMPLATEPARSEREMAILADDRESSREQUESTERAKONADITEST_H
