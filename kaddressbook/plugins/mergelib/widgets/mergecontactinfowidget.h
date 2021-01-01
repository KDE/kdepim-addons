/*
   SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTINFOWIDGET_H
#define MERGECONTACTINFOWIDGET_H

#include <QWidget>

#include <AkonadiCore/Item>
class QLabel;
namespace KAddressBookGrantlee {
class GrantleeContactViewer;
}

class QStackedWidget;
namespace KABMergeContacts {
class MergeContactInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MergeContactInfoWidget(QWidget *parent = nullptr);
    ~MergeContactInfoWidget() override;

public Q_SLOTS:
    void setContact(const Akonadi::Item &item);

private:
    QStackedWidget *mStackWidget = nullptr;
    QLabel *mNoContactSelected = nullptr;
    KAddressBookGrantlee::GrantleeContactViewer *mContactViewer = nullptr;
};
}

#endif // MERGECONTACTINFOWIDGET_H
