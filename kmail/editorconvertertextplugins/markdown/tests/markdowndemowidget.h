/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QTextEdit;
class MarkdownPreviewWidget;
class MarkdownDemoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownDemoWidget(QWidget *parent = nullptr);
    ~MarkdownDemoWidget() override = default;

private:
    QTextEdit *mEdit = nullptr;
    MarkdownPreviewWidget *mPreview = nullptr;
};
