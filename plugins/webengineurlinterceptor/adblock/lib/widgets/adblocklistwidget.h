/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QListWidget>

class QPaintEvent;
class QEvent;
namespace AdBlock
{
class AdBlockListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AdBlockListWidget(QWidget *parent = nullptr);
    ~AdBlockListWidget() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    void changeEvent(QEvent *event) override;

private:
    void generalPaletteChanged();
    QColor mTextColor;
};
}
