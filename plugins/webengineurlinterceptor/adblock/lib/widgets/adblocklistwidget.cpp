/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblocklistwidget.h"

#include <KLocalizedString>

#include <QPaintEvent>
#include <QPainter>

using namespace AdBlock;
AdBlockListWidget::AdBlockListWidget(QWidget *parent)
    : QListWidget(parent)
{
}

AdBlockListWidget::~AdBlockListWidget() = default;

void AdBlockListWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        generalPaletteChanged();
    }
    QListWidget::changeEvent(event);
}

void AdBlockListWidget::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void AdBlockListWidget::paintEvent(QPaintEvent *event)
{
    if (!model() || model()->rowCount() == 0) {
        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, i18n("No subscription added"));
    } else {
        QListWidget::paintEvent(event);
    }
}
