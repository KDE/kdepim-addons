/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "scamconfiguresettings_private_export.h"
#include <MessageViewer/ScamDetectionInfo>
#include <QString>

namespace ScamConfigureUtils
{
[[nodiscard]] QString convertEnumToString(MessageViewer::ScamDetectionInfo::ScamDetectionField flag);
};
