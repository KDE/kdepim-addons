/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GearySettings_H
#define GearySettings_H

#include <ImportWizard/AbstractSettings>

class QSettings;

class GearySettings : public AbstractSettings
{
public:
    explicit GearySettings(const QString &filename);
    ~GearySettings();
    void importSettings();
private:
    void readImapAccount();
    void readIdentity();
    void readGlobalSettings();
    void readTransport();
    QSettings *settings = nullptr;
};

#endif // ClawsMailSettings_H
