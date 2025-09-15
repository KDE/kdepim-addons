/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QTreeView>

class CheckFolderSizeAccountTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CheckFolderSizeAccountTreeView(QWidget *parent = nullptr);
    ~CheckFolderSizeAccountTreeView() override;

private:
    void slotCustomContextMenuRequested(const QPoint &pos);
};
