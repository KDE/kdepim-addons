/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QTextEdit>

class AutoGenerateAnswersEditorTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit AutoGenerateAnswersEditorTextEdit(QWidget *parent = nullptr);
    ~AutoGenerateAnswersEditorTextEdit() override;
};
