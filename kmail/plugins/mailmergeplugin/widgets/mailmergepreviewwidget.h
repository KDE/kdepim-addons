/*
  SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QWidget>

class MailMergePreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MailMergePreviewWidget(QWidget *parent = nullptr);
    ~MailMergePreviewWidget() override;
};
