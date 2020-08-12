/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPFOLDERTREEVIEW_H
#define SELECTIMAPFOLDERTREEVIEW_H

#include <QTreeView>
#include <QColor>

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
    LoadingStatus mStatus;
};

#endif // SELECTIMAPFOLDERTREEVIEW_H
