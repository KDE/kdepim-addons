/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomlabel.h"
#include <KLocalizedString>

ZoomLabel::ZoomLabel(QWidget *parent)
    : QLabel(parent)
{
    setZoomLabel(100);
}

ZoomLabel::~ZoomLabel() = default;

void ZoomLabel::setZoomLabel(int value)
{
    setText(value == 100 ? QString() : i18n("Zoom: %1%", value));
}

#include "moc_zoomlabel.cpp"
