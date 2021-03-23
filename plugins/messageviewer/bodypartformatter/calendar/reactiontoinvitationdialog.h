/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
namespace KPIMTextEdit
{
class PlainTextEditorWidget;
}

class ReactionToInvitationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReactionToInvitationDialog(QWidget *parent = nullptr);
    ~ReactionToInvitationDialog() override;

    QString comment() const;

private:
    void slotTextChanged();
    void writeConfig();
    void readConfig();
    KPIMTextEdit::PlainTextEditorWidget *mPlainTextEditor = nullptr;
    QPushButton *mOkButton = nullptr;
};

