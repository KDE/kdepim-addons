/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfigureutils.h"
#include <KLocalizedString>
QString ScamConfigureUtils::convertEnumToString(MessageViewer::ScamDetectionInfo::ScamDetectionField flag)
{
    switch (flag) {
    case MessageViewer::ScamDetectionInfo::ScamDetectionField::None:
        break;
    case MessageViewer::ScamDetectionInfo::ScamDetectionField::DisableAll:
        return i18n("Disable All Check");
    case MessageViewer::ScamDetectionInfo::ScamDetectionField::RedirectUrl:
        return i18n("Redirect Url");
    case MessageViewer::ScamDetectionInfo::ScamDetectionField::HasIp:
        return i18n("Has Ip");
    }
    return {};
}
