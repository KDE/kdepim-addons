/*
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATELINKWIDGET_H
#define MARKDOWNCREATELINKWIDGET_H

#include <QWidget>
#include "markdownlib_private_export.h"
class QLineEdit;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownCreateLinkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownCreateLinkWidget(QWidget *parent = nullptr);
    ~MarkdownCreateLinkWidget() override;
    Q_REQUIRED_RESULT QString linkStr() const;

Q_SIGNALS:
    void enabledOkButton(bool enabled);

private:
    void slotEnableButton();
    QLineEdit *mTitle = nullptr;
    QLineEdit *mLink = nullptr;
};

#endif // MARKDOWNCREATELINKWIDGET_H
