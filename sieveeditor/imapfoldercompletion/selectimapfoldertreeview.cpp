/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "selectimapfoldertreeview.h"

#include <KLocalizedString>
#include <QPainter>

SelectImapFolderTreeView::SelectImapFolderTreeView(QWidget *parent)
    : QTreeView(parent)
    , mStatus(InProgress)
{
}

SelectImapFolderTreeView::~SelectImapFolderTreeView()
{
}

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
