/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "akonadiresourcesstatustool.h"
#include "common/toolutils.h"
#include <Akonadi/AgentInstance>
#include <Akonadi/AgentManager>
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

using namespace Qt::Literals::StringLiterals;
namespace
{
[[nodiscard]] QString statusToString(Akonadi::AgentInstance::Status status)
{
    switch (status) {
    case Akonadi::AgentInstance::Idle:
        return u"idle"_s;
    case Akonadi::AgentInstance::Running:
        return u"running"_s;
    case Akonadi::AgentInstance::Broken:
        return u"broken"_s;
    case Akonadi::AgentInstance::NotConfigured:
        return u"not configured"_s;
    }
    return u"unknown"_s;
}
}
AkonadiResourcesStatusTool::AkonadiResourcesStatusTool() = default;
AkonadiResourcesStatusTool::~AkonadiResourcesStatusTool() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolTool AkonadiResourcesStatusTool::definition() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolTool tool =
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool::createTool(u"akonadi_resources_status"_s,
                                                                               u"List Akonadi resources and their status"_s,
                                                                               QMap<QString, QJsonObject>{});

    TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations annotation;
    annotation.setReadOnlyHint(true);
    annotation.setOpenWorldHint(false);
    tool.setTitle(i18n("Akonadi Resources Status"));
    tool.setAnnotations(annotation);
    ToolUtils::addToolMeta(tool, ToolUtils::Akonadi);
    return tool;
}

void AkonadiResourcesStatusTool::call(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    const auto list = Akonadi::AgentManager::self()->instances();
    QStringList entries;
    entries.reserve(list.count());
    for (const Akonadi::AgentInstance &instance : list) {
        if (instance.type().capabilities().contains(u"Resource"_s)) {
            QString entry = u"%1 (%2): %3, %4"_s.arg(instance.name(),
                                                     instance.identifier(),
                                                     statusToString(instance.status()),
                                                     instance.isOnline() ? u"online"_s : u"offline"_s);
            if (const QString message = instance.statusMessage(); !message.isEmpty()) {
                entry += u" - "_s + message;
            }
            entries.append(entry);
        }
    }
    if (entries.isEmpty()) {
        call->finishWithText(i18n("No Akonadi resource found"));
    } else {
        call->finishWithText(entries.join(u'\n'));
    }
}