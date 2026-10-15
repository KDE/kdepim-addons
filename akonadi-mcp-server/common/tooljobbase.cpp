/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "tooljobbase.h"
#include "akonadimcpprotocol_debug.h"
#include <KJob>
#include <KLocalizedString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>

ToolJobBase::ToolJobBase(QObject *parent)
    : QObject{parent}
{
}

ToolJobBase::~ToolJobBase() = default;

bool ToolJobBase::canStart() const
{
    return mToolCall;
}

void ToolJobBase::start()
{
    if (!canStart()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << metaObject()->className() << "can't start";
        finish(invalidArgumentsMessage(), true);
        return;
    }
    connect(mToolCall, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall::cancelled, this, &ToolJobBase::slotCancelled);
    startJob();
}

QString ToolJobBase::invalidArgumentsMessage() const
{
    return i18n("Invalid arguments");
}

void ToolJobBase::setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call)
{
    mToolCall = call;
}

void ToolJobBase::setCurrentJob(KJob *job)
{
    mCurrentJob = job;
}

bool ToolJobBase::hasToolCall() const
{
    return mToolCall;
}

void ToolJobBase::slotCancelled()
{
    if (mCurrentJob) {
        mCurrentJob->kill();
    }
    deleteLater();
}

bool ToolJobBase::checkJobResult(KJob *job, const KLocalizedString &errorMessage)
{
    if (!mToolCall) {
        deleteLater();
        return false;
    }
    if (job->error()) {
        qCWarning(AKONADI_MCP_PROTOCOL_LOG) << metaObject()->className() << "job failed:" << job->errorString();
        finish(errorMessage.subs(job->errorString()).toString(), true);
        return false;
    }
    return true;
}

void ToolJobBase::finish(const QString &text, bool isError)
{
    if (mToolCall) {
        mToolCall->finishWithText(text, isError);
    }
    deleteLater();
}

#include "moc_tooljobbase.cpp"
