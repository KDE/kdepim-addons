/*
  SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QDialog>

class MailMergePreviewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MailMergePreviewDialog(QWidget *parent = nullptr);
    ~MailMergePreviewDialog() override;
};
