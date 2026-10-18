/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markmailtooljob.h"

MarkMailToolJob::MarkMailToolJob(QObject *parent)
    : QObject{parent}
{
}

MarkMailToolJob::~MarkMailToolJob() = default;

#include "moc_markmailtooljob.cpp"
