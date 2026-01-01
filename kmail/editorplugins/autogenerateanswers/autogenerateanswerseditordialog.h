/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>
class AutoGenerateAnswersEditorWidget;
class AutoGenerateAnswersEditorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AutoGenerateAnswersEditorDialog(QWidget *parent = nullptr);
    ~AutoGenerateAnswersEditorDialog() override;

    void setAnswer(const QString &str);

Q_SIGNALS:
    void insertText(const QString &str);

private:
    void readConfig();
    void writeConfig();
    AutoGenerateAnswersEditorWidget *const mAutoGenerateAnswersEditorWidget;
};
