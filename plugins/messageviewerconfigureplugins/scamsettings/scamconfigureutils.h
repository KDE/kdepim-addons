/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <MessageViewer/ScamDetectionInfo>
#include <QString>

namespace ScamConfigureUtils
{
[[nodiscard]] QString convertEnumToString(MessageViewer::ScamDetectionInfo::ScamDetectionField flag);
};
