/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include <Akonadi/Item>
class QLabel;
namespace KAddressBookGrantlee
{
class GrantleeContactViewer;
}

class QStackedWidget;
namespace KABMergeContacts
{
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
    KAddressBookGrantlee::GrantleeContactViewer *const mContactViewer;
};
}
