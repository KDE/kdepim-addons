/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKBLOCKABLEELEMENTGUI_H
#define ADBLOCKBLOCKABLEELEMENTGUI_H

#include <QWidget>
class QWebEngineView;
namespace AdBlock {
class AdBlockResult;
}

class AdblockBlockableElementGui : public QWidget
{
    Q_OBJECT
public:
    explicit AdblockBlockableElementGui(QWidget *parent = nullptr);
    ~AdblockBlockableElementGui();

public Q_SLOTS:
    void slotSearchAdblock();

private:
    void slotSearchItemsDone(const QVector<AdBlock::AdBlockResult> &result);
    QWebEngineView *mWebEngineView = nullptr;
};

#endif // ADBLOCKBLOCKABLEELEMENTGUI_H
