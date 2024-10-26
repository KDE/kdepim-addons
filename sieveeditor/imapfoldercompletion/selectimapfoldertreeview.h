/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QColor>
#include <QTreeView>

class SelectImapFolderTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit SelectImapFolderTreeView(QWidget *parent);
    ~SelectImapFolderTreeView() override;
    enum LoadingStatus {
        InProgress = 0,
        Success,
        Failed
    };

    void setStatus(LoadingStatus status);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void generalPaletteChanged();
    QColor mTextColor;
    LoadingStatus mStatus = InProgress;
};
