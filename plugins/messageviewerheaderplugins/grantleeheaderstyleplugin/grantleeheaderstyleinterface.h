/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
