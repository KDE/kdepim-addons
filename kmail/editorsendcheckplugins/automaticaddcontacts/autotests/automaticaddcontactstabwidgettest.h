/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSTabWIDGETTEST_H
#define AUTOMATICADDCONTACTSTabWIDGETTEST_H

#include <QObject>
class QStandardItemModel;
class AutomaticAddContactsTabWidget;
class AutomaticAddContactsTabWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsTabWidgetTest(QObject *parent = nullptr);
    ~AutomaticAddContactsTabWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldResetValue();

private:
    AutomaticAddContactsTabWidget *createContactWidget();
    QStandardItemModel *mComboboxModel = nullptr;
};

#endif // AUTOMATICADDCONTACTSTabWIDGETTEST_H
