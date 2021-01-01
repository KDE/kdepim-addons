/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSConfigureWIDGETTEST_H
#define AUTOMATICADDCONTACTSConfigureWIDGETTEST_H

#include <QObject>
class AutomaticAddContactsConfigureWidget;
class AutomaticAddContactsConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsConfigureWidgetTest(QObject *parent = nullptr);
    ~AutomaticAddContactsConfigureWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // AUTOMATICADDCONTACTSConfigureWIDGETTEST_H
