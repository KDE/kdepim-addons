/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSELECTLISTWIDGET_H
#define MERGECONTACTSELECTLISTWIDGET_H

#include <AkonadiCore/Item>
#include "kaddressbookmergelib_export.h"
#include "job/mergecontacts.h"
#include <QWidget>
#include <QIcon>
class QLabel;
class QListWidget;
namespace KContacts {
class Addressee;
}
namespace KABMergeContacts {
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectListWidget(QWidget *parent = nullptr);
    ~MergeContactSelectListWidget();

    void setContacts(MergeContacts::ConflictInformation conflictType, const KContacts::Addressee::List &lst);
    Q_REQUIRED_RESULT int selectedContact() const;
    MergeContacts::ConflictInformation conflictType() const;
    Q_REQUIRED_RESULT bool verifySelectedInfo() const;
private:
    void fillList(const KContacts::Addressee::List &lst);
    void updateTitle();
    void addItem(const QString &str, const QIcon &icon = QIcon());
    QLabel *mTitle = nullptr;
    QListWidget *mSelectListWidget = nullptr;
    MergeContacts::ConflictInformation mConflictType;
};
}

#endif // MERGECONTACTSELECTLISTWIDGET_H
