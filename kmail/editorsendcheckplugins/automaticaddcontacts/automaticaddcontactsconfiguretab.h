/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef AUTOMATICADDCONTACTSCONFIGURETAB_H
#define AUTOMATICADDCONTACTSCONFIGURETAB_H

#include <QWidget>
class QTabWidget;
class AutomaticAddContactsTabWidget;

namespace KIdentityManagement {
class IdentityManager;
}

class AutomaticAddContactsConfigureTab : public QWidget
{
    Q_OBJECT
public:
    explicit AutomaticAddContactsConfigureTab(QWidget *parent = nullptr);
    ~AutomaticAddContactsConfigureTab() override;

    void loadSettings();
    void saveSettings();
    void resetSettings();

Q_SIGNALS:
    void configureChanged();

private:
    void initTab(KIdentityManagement::IdentityManager *identityManager);
    QTabWidget *mTabWidget = nullptr;
    QList<AutomaticAddContactsTabWidget *> mListTabWidget;
};

#endif // AUTOMATICADDCONTACTSCONFIGURETAB_H
