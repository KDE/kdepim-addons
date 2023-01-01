/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "openurlwith_private_export.h"
#include <QWidget>
class QLineEdit;
class KUrlRequester;
class LIBOPENURLWITHCONFIGURE_TESTS_EXPORT OpenUrlWithConfigureCreateWidget : public QWidget
{
    Q_OBJECT
public:
    struct OpenUrlWithInfo {
        QString command;
        QString commandLines;
        QString url;
        Q_REQUIRED_RESULT bool isValid() const;
    };

    explicit OpenUrlWithConfigureCreateWidget(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureCreateWidget() override;

    Q_REQUIRED_RESULT OpenUrlWithInfo info() const;
    void setInfo(const OpenUrlWithInfo &i);
Q_SIGNALS:
    void updateOkButton(bool enabled);

private:
    void slotLinkClicked(const QString &link);
    void slotInfoChanged();
    QString mCommandWhatsThis;
    QLineEdit *const mServerName;
    QLineEdit *const mCommandLine;
    KUrlRequester *const mExecutable;
};
