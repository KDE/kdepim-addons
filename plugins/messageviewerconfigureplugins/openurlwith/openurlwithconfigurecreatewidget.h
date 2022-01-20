/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "openurlwith_private_export.h"
#include <QWidget>
class QLineEdit;
class LIBOPENURLWITHCONFIGURE_TESTS_EXPORT OpenUrlWithConfigureCreateWidget : public QWidget
{
    Q_OBJECT
public:
    struct OpenUrlWithInfo {
        QString command;
        QString url;
    };

    explicit OpenUrlWithConfigureCreateWidget(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureCreateWidget() override;

    Q_REQUIRED_RESULT OpenUrlWithInfo info() const;
    void setInfo(const OpenUrlWithInfo &i);

private:
    QLineEdit *const mServerName;
    QLineEdit *const mCommand;
};
