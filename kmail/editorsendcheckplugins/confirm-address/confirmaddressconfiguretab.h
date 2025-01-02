/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QTabWidget;
class KConfigGroup;
class ConfirmAddressConfigureTabWidget;
namespace KIdentityManagementCore
{
class IdentityManager;
}

class ConfirmAddressConfigureTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureTab(QWidget *parent = nullptr);
    ~ConfirmAddressConfigureTab() override;

    void loadSettings(const KConfigGroup &grp);
    void saveSettings(KConfigGroup &grp);
    void resetSettings();

Q_SIGNALS:
    void configureChanged();

private:
    void initTab(KIdentityManagementCore::IdentityManager *identityManager);
    QTabWidget *const mTabWidget;
    QList<ConfirmAddressConfigureTabWidget *> mListTabWidget;
};
