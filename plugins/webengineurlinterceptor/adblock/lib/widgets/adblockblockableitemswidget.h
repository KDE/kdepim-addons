/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblocklib_export.h"
#include <QWidget>
namespace PimCommon
{
class CustomTreeView;
}
namespace AdBlock
{
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

        MaxTypeElement,
    };

    explicit AdBlockBlockableItemsWidget(QWidget *parent = nullptr);
    ~AdBlockBlockableItemsWidget() override;

    void setAdblockResult(const QVector<AdBlock::AdBlockResult> &result);
    void saveFilters();

    Q_REQUIRED_RESULT static QString elementType(AdBlockBlockableItemsWidget::TypeElement type);
    Q_REQUIRED_RESULT static QString elementTypeToI18n(AdBlockBlockableItemsWidget::TypeElement type);

private:
    void slotCustomContextMenuRequested(const QPoint &);
    void slotCopyFilterItem();
    void slotOpenItem();
    void slotBlockItem();
    void slotCopyItem();
    void slotRemoveFilter();
    enum BlockType {
        FilterValue = 0,
        Url,
        Type,
    };
    enum TypeItem {
        Element = Qt::UserRole + 1,
    };

    void writeConfig();
    void readConfig();
    PimCommon::CustomTreeView *mCustomTreeView = nullptr;
};
}
