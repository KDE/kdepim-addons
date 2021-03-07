/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TEST_HEADERSTYLEMENU_GUI_H
#define TEST_HEADERSTYLEMENU_GUI_H

#include <QWidget>
class QTextEdit;
namespace MessageViewer
{
class HeaderStylePlugin;
}

class HeaderStyleMenuTest : public QWidget
{
    Q_OBJECT
public:
    explicit HeaderStyleMenuTest(QWidget *parent = nullptr);
    ~HeaderStyleMenuTest() override;
private Q_SLOTS:
    void styleChanged(MessageViewer::HeaderStylePlugin *plugin);

private:
    QTextEdit *mTextEdit = nullptr;
};

#endif
