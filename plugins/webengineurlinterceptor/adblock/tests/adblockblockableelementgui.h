/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QWebEngineView;
namespace AdBlock
{
struct AdBlockResult;
}

class AdblockBlockableElementGui : public QWidget
{
    Q_OBJECT
public:
    explicit AdblockBlockableElementGui(QWidget *parent = nullptr);
    ~AdblockBlockableElementGui() override;

public Q_SLOTS:
    void slotSearchAdblock();

private:
    void slotSearchItemsDone(const QVector<AdBlock::AdBlockResult> &result);
    QWebEngineView *mWebEngineView = nullptr;
};
