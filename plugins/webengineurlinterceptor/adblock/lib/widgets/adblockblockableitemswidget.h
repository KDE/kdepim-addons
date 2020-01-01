/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef ADBLOCKBLOCKABLEITEMSWIDGET_H
#define ADBLOCKBLOCKABLEITEMSWIDGET_H

#include <QWidget>
#include "adblocklib_export.h"
namespace PimCommon {
class CustomTreeView;
}
namespace AdBlock {
struct AdBlockResult;
class ADBLOCKLIB_EXPORT AdBlockBlockableItemsWidget : public QWidget
{
    Q_OBJECT
public:
    enum TypeElement {
        None = 0,
        Image,
        Script,
        StyleSheet,
        Font,
        Frame,
        XmlRequest,
        Object,
        Media,
        Popup,

        MaxTypeElement
    };

    explicit AdBlockBlockableItemsWidget(QWidget *parent = nullptr);
    ~AdBlockBlockableItemsWidget();

    void setAdblockResult(const QVector<AdBlock::AdBlockResult> &result);
    void saveFilters();

    static QString elementType(AdBlockBlockableItemsWidget::TypeElement type);
    static QString elementTypeToI18n(AdBlockBlockableItemsWidget::TypeElement type);

private:
    void customContextMenuRequested(const QPoint &);
    void slotCopyFilterItem();
    void slotOpenItem();
    void slotBlockItem();
    void slotCopyItem();
    void slotRemoveFilter();
    enum BlockType {
        FilterValue = 0,
        Url,
        Type
    };
    enum TypeItem {
        Element = Qt::UserRole + 1
    };

    void writeConfig();
    void searchBlockableItems();
    void readConfig();
    PimCommon::CustomTreeView *mListItems = nullptr;
};
}
#endif // ADBLOCKBLOCKABLEITEMSWIDGET_H
