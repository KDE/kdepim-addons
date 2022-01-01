/*
  SPDX-FileCopyrightText: 2021-2022 Laurent Montel <montel@kde.org>

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
