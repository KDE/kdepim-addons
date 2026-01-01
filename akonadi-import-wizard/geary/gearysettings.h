/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractSettings>

class QSettings;

class GearySettings : public AbstractSettings
{
public:
    explicit GearySettings(const QString &filename);
    ~GearySettings() override;
    void importSettings();

private:
    void readImapAccount();
    void readIdentity();
    void readGlobalSettings();
    void readTransport();
    QSettings *const settings;
};
