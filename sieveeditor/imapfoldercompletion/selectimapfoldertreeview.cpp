/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapfoldertreeview.h"

#include <KLocalizedString>
#include <QPainter>

SelectImapFolderTreeView::SelectImapFolderTreeView(QWidget *parent)
    : QTreeView(parent)
{
}

SelectImapFolderTreeView::~SelectImapFolderTreeView() = default;

void SelectImapFolderTreeView::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void SelectImapFolderTreeView::setStatus(LoadingStatus status)
{
    mStatus = status;
}

void SelectImapFolderTreeView::paintEvent(QPaintEvent *event)
{
    QString label;
    switch (mStatus) {
    case Failed:
        label = i18n("Unable to load folder list");
        break;
    case InProgress:
        label = i18n("Loading in progress...");
        break;
    case Success:
        QTreeView::paintEvent(event);
        return;
    }

    QPainter p(viewport());

    QFont font = p.font();
    font.setItalic(true);
    p.setFont(font);

    if (!mTextColor.isValid()) {
        generalPaletteChanged();
    }
    p.setPen(mTextColor);

    p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, label);
}

#include "moc_selectimapfoldertreeview.cpp"
