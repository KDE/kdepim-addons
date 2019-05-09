/*
    Copyright (C) 2019 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef MARKDOWNCREATEIMAGEWIDGET_H
#define MARKDOWNCREATEIMAGEWIDGET_H

#include <QWidget>
#include "markdownlib_private_export.h"
class QLineEdit;
class QCheckBox;
class QLabel;
class QSpinBox;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownCreateImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownCreateImageWidget(QWidget *parent = nullptr);
    ~MarkdownCreateImageWidget();
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
