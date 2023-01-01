/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QTabWidget;
class AutomaticAddContactsTabWidget;

namespace KIdentityManagement
{
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
    QTabWidget *const mTabWidget;
    QList<AutomaticAddContactsTabWidget *> mListTabWidget;
};
