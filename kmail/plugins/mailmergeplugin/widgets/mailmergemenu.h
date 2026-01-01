/*
  SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/
#pragma once

#include <QMenu>

class MailMergeMenu : public QMenu
{
    Q_OBJECT
public:
    explicit MailMergeMenu(QWidget *parent = nullptr);
    ~MailMergeMenu() override;
};
