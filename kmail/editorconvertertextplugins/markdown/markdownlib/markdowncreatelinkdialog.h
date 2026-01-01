/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "libkmailmarkdown_export.h"
#include <QDialog>
class MarkdownCreateLinkWidget;
class QPushButton;
class LIBKMAILMARKDOWN_EXPORT MarkdownCreateLinkDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MarkdownCreateLinkDialog(QWidget *parent = nullptr);
    ~MarkdownCreateLinkDialog() override;
    [[nodiscard]] QString linkStr() const;

private:
    void writeConfig();
    void readConfig();
    void slotEnabledOkButton(bool enabled);
    MarkdownCreateLinkWidget *const mMarkdownCreateLinkWidget;
    QPushButton *mOkButton = nullptr;
};
