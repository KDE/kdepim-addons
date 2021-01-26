/*
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATEIMAGEWIDGET_H
#define MARKDOWNCREATEIMAGEWIDGET_H

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
    Q_REQUIRED_RESULT QString linkStr() const;

Q_SIGNALS:
    void enabledOkButton(bool enabled);

private:
    void slotKeepOriginalSizeChanged();
    void slotEnableButton();
    QLineEdit *mTitle = nullptr;
    QLineEdit *mImageUrl = nullptr;
    QLineEdit *mAlternateText = nullptr;
    QCheckBox *mKeepOriginalSize = nullptr;
    QLabel *mLabWidth = nullptr;
    QSpinBox *mWidth = nullptr;
    QLabel *mLabHeight = nullptr;
    QSpinBox *mHeight = nullptr;
};

#endif // MARKDOWNCREATEIMAGEWIDGET_H
