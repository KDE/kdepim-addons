/*
   SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "openurlwith_private_export.h"
#include <QWidget>
class QListWidget;
class QPushButton;
class OpenUrlWithConfigureItem;
namespace MessageViewer
{
class OpenWithUrlInfo;
}
class LIBOPENURLWITHCONFIGURE_TESTS_EXPORT OpenUrlWithConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenUrlWithConfigureWidget(QWidget *parent = nullptr);
    ~OpenUrlWithConfigureWidget() override;
    void loadSettings();
    void writeSettings();

private:
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void slotCustomContextMenuRequested(const QPoint &p);
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void slotAddRule();
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void slotEditRule();
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void slotRemoveRule();
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void displayText(const MessageViewer::OpenWithUrlInfo &r, OpenUrlWithConfigureItem *item);
    LIBOPENURLWITHCONFIGURE_NO_EXPORT void updateButtons();
    QListWidget *const mListWidget;
    QPushButton *const mAddRule;
    QPushButton *const mRemoveRule;
    QPushButton *const mModifyRule;
};
