/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QTreeWidget;
class CheckFolderSizeAccountPluginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountPluginWidget(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountPluginWidget() override;

private:
    QTreeWidget *const mTreeWidget;
};
