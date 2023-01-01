/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractSettings>

class KConfigGroup;

class OperaSettings : public AbstractSettings
{
public:
    explicit OperaSettings(const QString &filename);
    ~OperaSettings() override;

    void importSettings();

private:
    void readAccount(const KConfigGroup &grp);
    void readTransport(const KConfigGroup &grp);
    void readGlobalAccount(const KConfigGroup &grp);
    void readIdentity(const KConfigGroup &grp);
    const QString mFileName;
};
