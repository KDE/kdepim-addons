/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QPlainTextEdit;
class AutoGenerateAnswersEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutoGenerateAnswersEditorWidget(QWidget *parent = nullptr);
    ~AutoGenerateAnswersEditorWidget() override;

private:
    QPlainTextEdit *const mPlainTextEdit;
};
