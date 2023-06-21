/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergejob.h"

using namespace MailMerge;

MailMergeJob::MailMergeJob(QObject *parent)
    : QObject(parent)
{
}

MailMergeJob::~MailMergeJob()
{
}

void MailMergeJob::start()
{
}

#include "moc_mailmergejob.cpp"
