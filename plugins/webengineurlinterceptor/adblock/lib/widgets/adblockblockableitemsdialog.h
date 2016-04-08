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

#ifndef ADBLOCKBLOCKABLEITEMSDIALOG_H
#define ADBLOCKBLOCKABLEITEMSDIALOG_H

#include <QDialog>
#include "adblocklib_export.h"
class QWebEngineView;
namespace AdBlock
{
class AdBlockBlockableItemsWidget;
class ADBLOCKLIB_EXPORT AdBlockBlockableItemsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdBlockBlockableItemsDialog(QWidget *parent = Q_NULLPTR);
    ~AdBlockBlockableItemsDialog();

    void saveFilters();

    void setWebEngineView(QWebEngineView *view);
private:
    void writeConfig();
    void readConfig();
    AdBlockBlockableItemsWidget *mBlockableItems;
};
}
#endif // ADBLOCKBLOCKABLEITEMSDIALOG_H
