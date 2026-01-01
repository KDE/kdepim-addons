/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractSettings>

class KConfigGroup;

class PMailSettings : public AbstractSettings
{
public:
    explicit PMailSettings(const QString &filename);
    ~PMailSettings() override;

    void importSettings();

private:
    void readIdentity(const KConfigGroup &group);
    const QString mFileName;
};
