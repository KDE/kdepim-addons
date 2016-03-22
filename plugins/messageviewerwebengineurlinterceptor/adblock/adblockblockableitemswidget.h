/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ADBLOCKBLOCKABLEITEMSWIDGET_H
#define ADBLOCKBLOCKABLEITEMSWIDGET_H

#include <QWidget>
namespace PimCommon
{
class CustomTreeView;
}
class QWebEngineView;
class AdBlockBlockableItemsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdBlockBlockableItemsWidget(QWidget *parent = Q_NULLPTR);
    ~AdBlockBlockableItemsWidget();

    void setWebEngineView(QWebEngineView *view);

private Q_SLOTS:
    void handleSearchBlockableItems(const QVariant &var);
    void customContextMenuRequested(const QPoint &);
    void slotCopyFilterItem();
    void slotOpenItem();
    void slotBlockItem();
    void slotCopyItem();
private:
    enum BlockType {
        FilterValue = 0,
        Url,
        Type
    };

    void writeConfig();
    void searchBlockableItems();
    void readConfig();
    PimCommon::CustomTreeView *mListItems;
    QWebEngineView *mWebEngineView;
};

#endif // ADBLOCKBLOCKABLEITEMSWIDGET_H
