/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSTABWIDGET_H
#define AUTOMATICADDCONTACTSTABWIDGET_H

#include <QWidget>
class QCheckBox;

namespace Akonadi {
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
    QCheckBox *mEnabled = nullptr;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    uint mIdentity = 0;
};

#endif // AUTOMATICADDCONTACTSTABWIDGET_H
