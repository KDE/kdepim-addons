/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class QComboBox;
class QToolButton;
namespace AdBlock
{
class AdBlockAddSubscriptionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdBlockAddSubscriptionDialog(const QStringList &excludeList, QWidget *parent = nullptr);
    ~AdBlockAddSubscriptionDialog() override;

    void selectedList(QString &name, QString &url);

private:
    void slotShowList();
    void initializeList(const QStringList &excludeList);
    QComboBox *mListSubscription = nullptr;
    QToolButton *mShowList = nullptr;
};
}
