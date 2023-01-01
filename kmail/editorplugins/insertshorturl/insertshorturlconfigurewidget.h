/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QComboBox;
class InsertShorturlConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InsertShorturlConfigureWidget(QWidget *parent = nullptr);
    ~InsertShorturlConfigureWidget() override;

    void writeConfig();

private:
    void slotChanged();
    void loadConfig();
    bool mChanged = false;
    QComboBox *const mShortUrlServer;
};
