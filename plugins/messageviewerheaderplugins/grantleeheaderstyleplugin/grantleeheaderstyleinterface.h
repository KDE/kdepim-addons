/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEEHEADERSTYLEINTERFACE_H
#define GRANTLEEHEADERSTYLEINTERFACE_H

#include <MessageViewer/HeaderStyleInterface>

namespace GrantleeTheme
{
class ThemeManager;
}

class GrantleeHeaderStylePluginTest;

namespace MessageViewer
{
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
