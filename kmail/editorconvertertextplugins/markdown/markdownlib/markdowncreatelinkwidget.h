/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "markdownlib_private_export.h"
#include <QWidget>
class QLineEdit;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownCreateLinkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownCreateLinkWidget(QWidget *parent = nullptr);
    ~MarkdownCreateLinkWidget() override;
    [[nodiscard]] QString linkStr() const;

Q_SIGNALS:
    void enabledOkButton(bool enabled);

private:
    void slotEnableButton();
    QLineEdit *const mTitle;
    QLineEdit *const mLink;
};
