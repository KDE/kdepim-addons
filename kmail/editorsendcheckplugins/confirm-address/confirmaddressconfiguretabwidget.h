/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSCONFIGURETABWIDGET_H
#define CONFIRMADDRESSCONFIGURETABWIDGET_H

#include <QWidget>
class ConfirmAddressSimpleStringListEditor;
class KConfigGroup;
class QRadioButton;
class ConfirmAddressConfigureTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmAddressConfigureTabWidget(QWidget *parent = nullptr);
    ~ConfirmAddressConfigureTabWidget();

    void resetSettings();
    void loadSettings(const KConfigGroup &grp);
    void saveSettings(KConfigGroup &grp);

    void setIdentity(uint identity);

Q_SIGNALS:
    void configureChanged();

private:
    uint mIdentity = 0;
    ConfirmAddressSimpleStringListEditor *mDomainNameListEditor = nullptr;
    ConfirmAddressSimpleStringListEditor *mWhiteListEditor = nullptr;
    QRadioButton *mAcceptedDomain = nullptr;
    QRadioButton *mRejectedDomain = nullptr;
};

#endif // CONFIRMADDRESSCONFIGURETABWIDGET_H
