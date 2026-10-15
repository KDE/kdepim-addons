/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"

class ListAddressBooksToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit ListAddressBooksToolJob(QObject *parent = nullptr);
    ~ListAddressBooksToolJob() override;

protected:
    void startJob() override;

private:
    void slotResult(KJob *job);
};
