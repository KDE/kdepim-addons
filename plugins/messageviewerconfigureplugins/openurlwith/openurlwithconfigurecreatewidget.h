/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

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
        [[nodiscard]] bool isValid() const;
    };

    explicit OpenUrlWithConfigureCreateWidget(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureCreateWidget() override;

    [[nodiscard]] OpenUrlWithInfo info() const;
    void setInfo(const OpenUrlWithInfo &i);
Q_SIGNALS:
    void updateOkButton(bool enabled);

private:
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void slotLinkClicked(const QString &link);
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void slotInfoChanged();
    QString mCommandWhatsThis;
    QLineEdit *const mServerName;
    QLineEdit *const mCommandLine;
    KUrlRequester *const mExecutable;
};
