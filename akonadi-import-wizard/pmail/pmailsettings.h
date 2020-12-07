/*
   SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PMailSettings_H
#define PMailSettings_H

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
    QString mFileName;
};

#endif // ClawsMailSettings_H
