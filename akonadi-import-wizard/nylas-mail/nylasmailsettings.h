/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractSettings>

class NylasMailSettings : public AbstractSettings
{
public:
    explicit NylasMailSettings(const QString &filename);
    ~NylasMailSettings() override;
    void importSettings();

private:
    void readImapAccount();
    void readIdentity();
    void readGlobalSettings();
    void readTransport();
};

