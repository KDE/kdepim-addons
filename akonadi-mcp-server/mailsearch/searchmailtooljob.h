/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/tooljobbase.h"

class SearchMailToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit SearchMailToolJob(QObject *parent = nullptr);
    ~SearchMailToolJob() override;

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;
};
