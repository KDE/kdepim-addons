/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <KCalendarCore/Calendar>
#include <QObject>
#include <QPointer>

class KJob;
namespace Akonadi
{
class RecursiveItemFetchJob;
}
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServerToolCall;
}

class CalendarToolJobBase : public QObject
{
    Q_OBJECT
public:
    explicit CalendarToolJobBase(QObject *parent = nullptr);
    ~CalendarToolJobBase() override;

    [[nodiscard]] virtual bool canStart() const;

    void start();

    void setMcpProtocolServerToolCall(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall *call);

protected:
    [[nodiscard]] virtual QStringList mimeTypes() const = 0;
    [[nodiscard]] virtual QString generateResult(const KCalendarCore::Calendar::Ptr &calendar) const = 0;

private:
    void slotResult(KJob *job);
    void slotCancelled();
    QPointer<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolCall> mToolCall;
    QPointer<Akonadi::RecursiveItemFetchJob> mFetchJob;
};
