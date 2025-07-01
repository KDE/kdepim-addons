/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QSpinBox;
class CheckFolderSizeAccountPluginConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginConfigureWidget(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountPluginConfigureWidget() override;

    void load();
    void save();

private:
    QSpinBox *const mWarningSpinBox;
};
