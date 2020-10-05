/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FOLDERCONFIGURESETTINGSPAGEBASE_H
#define FOLDERCONFIGURESETTINGSPAGEBASE_H

#include <QWidget>
class QVBoxLayout;
class QGroupBox;
class FolderConfigureSettingsPageBase : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsPageBase(QWidget *parent = nullptr);
    ~FolderConfigureSettingsPageBase();
    Q_REQUIRED_RESULT bool wasModified() const;
protected:
    void addMainWidget(QWidget *widget);

    QVBoxLayout *const mMainLayout;
private:
    void slotModifyClicked(bool clicked);
    QWidget *mMainWidget = nullptr;
    QGroupBox *mGroupBox = nullptr;
};

#endif // FOLDERCONFIGURESETTINGSPAGEBASE_H
