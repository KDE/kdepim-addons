/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomlabel.h"
#include <KLocalizedString>

ZoomLabel::ZoomLabel(QWidget *parent)
    : QLabel(parent)
{
    setZoomLabel(100);
}

ZoomLabel::~ZoomLabel()
{
}

void ZoomLabel::setZoomLabel(int value)
{
    setText(value == 100 ? QString() : i18n("Zoom: %1%", value));
}
