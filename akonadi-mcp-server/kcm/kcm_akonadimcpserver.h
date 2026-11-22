/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_version.h"
#include <KCModule>
#if TEXTADDONSWIDGETS_VERSION >= QT_VERSION_CHECK(2, 3, 45)
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class MCPServerConfigurationModuleWidget;
}
#else
class QCheckBox;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpProtocolServerConfigureWidget;
}
#endif
class AkonadiMCPServerConfigurationModule : public KCModule
{
    Q_OBJECT
public:
    explicit AkonadiMCPServerConfigurationModule(QObject *parent, const KPluginMetaData &data);
    ~AkonadiMCPServerConfigurationModule() override;
    void load() override;
    void save() override;
    void defaults() override;

private:
#if TEXTADDONSWIDGETS_VERSION >= QT_VERSION_CHECK(2, 3, 45)
    TextAutoGenerateTextMcpProtocolWidgets::MCPServerConfigurationModuleWidget *const mConfigurationWidget;
#else
    void slotConfigChanged();
    void reloadServer();
    TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget *const mMcpProtocolServerConfigureWidget;
    QCheckBox *const mEnabled;
    QCheckBox *const mConfirmModify;
#endif
};
