/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "markdownlib_private_export.h"
#include <QWidget>
class QLineEdit;
class QCheckBox;
class QLabel;
class QSpinBox;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownCreateImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownCreateImageWidget(QWidget *parent = nullptr);
    ~MarkdownCreateImageWidget() override;
    [[nodiscard]] QString linkStr() const;

Q_SIGNALS:
    void enabledOkButton(bool enabled);

private:
    void slotKeepOriginalSizeChanged();
    void slotEnableButton();
    QLineEdit *const mTitle;
    QLineEdit *const mImageUrl;
    QLineEdit *const mAlternateText;
    QCheckBox *const mKeepOriginalSize;
    QLabel *const mLabWidth;
    QSpinBox *const mWidth;
    QLabel *const mLabHeight;
    QSpinBox *const mHeight;
};
