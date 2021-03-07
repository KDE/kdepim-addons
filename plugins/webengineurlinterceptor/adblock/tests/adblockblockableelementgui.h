/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKBLOCKABLEELEMENTGUI_H
#define ADBLOCKBLOCKABLEELEMENTGUI_H

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

#endif // ADBLOCKBLOCKABLEELEMENTGUI_H
