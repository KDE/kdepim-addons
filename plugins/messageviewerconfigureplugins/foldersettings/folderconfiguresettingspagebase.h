/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QVBoxLayout;
class QGroupBox;
class FolderConfigureSettingsPageBase : public QWidget
{
    Q_OBJECT
public:
    explicit FolderConfigureSettingsPageBase(QWidget *parent = nullptr);
    ~FolderConfigureSettingsPageBase() override;
    [[nodiscard]] bool wasModified() const;

protected:
    void addMainWidget(QWidget *widget);

    QVBoxLayout *const mMainLayout;

private:
    void slotModifyClicked(bool clicked);
    QWidget *mMainWidget = nullptr;
    QGroupBox *const mGroupBox;
};
