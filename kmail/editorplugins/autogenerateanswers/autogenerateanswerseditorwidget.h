/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QTextEdit;
class AutoGenerateAnswersEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutoGenerateAnswersEditorWidget(QWidget *parent = nullptr);
    ~AutoGenerateAnswersEditorWidget() override;

    void setAnswer(const QString &str);

private:
    QTextEdit *const mTextEdit;
};
