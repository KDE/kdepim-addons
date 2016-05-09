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
#include "adblocklib_export.h"
namespace PimCommon
{
class CustomTreeView;
}
namespace AdBlock
{
class AdBlockResult;
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

    explicit AdBlockBlockableItemsWidget(QWidget *parent = Q_NULLPTR);
    ~AdBlockBlockableItemsWidget();

    void setAdblockResult(const QVector<AdBlock::AdBlockResult> &result);

    static QString elementType(AdBlockBlockableItemsWidget::TypeElement type);
    static QString elementTypeToI18n(AdBlockBlockableItemsWidget::TypeElement type);
private Q_SLOTS:
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
    enum TypeItem {
        Element = Qt::UserRole + 1
    };

    void writeConfig();
    void searchBlockableItems();
    void readConfig();
    PimCommon::CustomTreeView *mListItems;
};
}
#endif // ADBLOCKBLOCKABLEITEMSWIDGET_H
