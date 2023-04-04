/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblocklib_export.h"
#include <QDialog>
namespace AdBlock
{
struct AdBlockResult;
class AdBlockBlockableItemsWidget;
class ADBLOCKLIB_EXPORT AdBlockBlockableItemsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdBlockBlockableItemsDialog(QWidget *parent = nullptr);
    ~AdBlockBlockableItemsDialog() override;

    void saveFilters();
    void setAdblockResult(const QList<AdBlock::AdBlockResult> &result);

    void accept() override;

private:
    void writeConfig();
    void readConfig();
    AdBlockBlockableItemsWidget *mBlockableItems = nullptr;
};
}
