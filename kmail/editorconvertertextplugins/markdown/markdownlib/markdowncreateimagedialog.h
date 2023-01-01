/*
    SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libkmailmarkdown_export.h"
#include <QDialog>
class MarkdownCreateImageWidget;
class QPushButton;
class LIBKMAILMARKDOWN_EXPORT MarkdownCreateImageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MarkdownCreateImageDialog(QWidget *parent = nullptr);
    ~MarkdownCreateImageDialog() override;
    Q_REQUIRED_RESULT QString linkStr() const;

private:
    void writeConfig();
    void readConfig();
    void slotEnabledOkButton(bool enabled);
    MarkdownCreateImageWidget *const mMarkdownCreateImageWidget;
    QPushButton *mOkButton = nullptr;
};
