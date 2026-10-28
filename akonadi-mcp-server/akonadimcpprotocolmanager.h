/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager>

class AkonadiMcpProtocolManager : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.akonadimcpprotocol")
public:
    explicit AkonadiMcpProtocolManager(QObject *parent = nullptr);
    ~AkonadiMcpProtocolManager() override;
    [[nodiscard]] bool start(const QString &url);

public Q_SLOTS:
    Q_SCRIPTABLE void reload();

private:
    void loadSettingsAndStart();
    bool mUrlFromCommandLine = false;
};
