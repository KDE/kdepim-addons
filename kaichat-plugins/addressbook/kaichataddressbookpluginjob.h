/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginJob>
class KJob;
class KAIChatAddressBookPluginJob : public TextAutoGenerateText::TextAutoGenerateTextToolPluginJob
{
    Q_OBJECT
public:
    explicit KAIChatAddressBookPluginJob(QObject *parent = nullptr);
    ~KAIChatAddressBookPluginJob() override;
    void start() override;

private:
    void slotContactEmailSearchDone(KJob *job);
    void slotContactBirthdaySearchDone(KJob *job);
};
