/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKBLOCKABLEITEMSDIALOG_H
#define ADBLOCKBLOCKABLEITEMSDIALOG_H

#include <QDialog>
#include "adblocklib_export.h"
namespace AdBlock {
struct AdBlockResult;
class AdBlockBlockableItemsWidget;
class ADBLOCKLIB_EXPORT AdBlockBlockableItemsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdBlockBlockableItemsDialog(QWidget *parent = nullptr);
    ~AdBlockBlockableItemsDialog() override;

    void saveFilters();
    void setAdblockResult(const QVector<AdBlock::AdBlockResult> &result);

    void accept() override;
private:
    void writeConfig();
    void readConfig();
    AdBlockBlockableItemsWidget *mBlockableItems = nullptr;
};
}
#endif // ADBLOCKBLOCKABLEITEMSDIALOG_H
