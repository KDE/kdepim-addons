/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#ifndef GRANTLEEHEADERSTYLEINTERFACE_H
#define GRANTLEEHEADERSTYLEINTERFACE_H

#include <messageviewer/headerstyleinterface.h>

namespace GrantleeTheme {
class ThemeManager;
}

class GrantleeHeaderStylePluginTest;

namespace MessageViewer {
class GrantleeHeaderStyleInterface : public MessageViewer::HeaderStyleInterface
{
    Q_OBJECT
public:
    explicit GrantleeHeaderStyleInterface(HeaderStylePlugin *plugin, QObject *parent = nullptr);
    ~GrantleeHeaderStyleInterface() override;

    void createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac) override;
    void activateAction() override;
private:
    void slotGrantleeHeaders();

    friend ::GrantleeHeaderStylePluginTest;
    GrantleeTheme::ThemeManager *mThemeManager = nullptr;
};
}

#endif // GRANTLEEHEADERSTYLEINTERFACE_H
