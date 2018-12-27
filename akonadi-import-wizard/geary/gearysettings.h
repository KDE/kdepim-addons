/*
   Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
