/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QCheckBox;

namespace Akonadi
{
class CollectionComboBox;
}
class QAbstractItemModel;
class AutomaticAddContactsTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsTabWidget(QWidget *parent = nullptr, QAbstractItemModel *model = nullptr);
    ~AutomaticAddContactsTabWidget() override;

    void resetSettings();
    void saveSettings();
    void loadSettings();
    void setIdentity(uint identity);
Q_SIGNALS:
    void configureChanged();

private:
    QCheckBox *const mEnabled;
    Akonadi::CollectionComboBox *const mCollectionCombobox;
    uint mIdentity = 0;
};
