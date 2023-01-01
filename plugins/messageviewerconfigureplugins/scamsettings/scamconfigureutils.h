/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "scamconfiguresettings_private_export.h"
#include <MessageViewer/ScamDetectionInfo>
#include <QString>

namespace ScamConfigureUtils
{
Q_REQUIRED_RESULT QString convertEnumToString(MessageViewer::ScamDetectionInfo::ScamDetectionField flag);
};
