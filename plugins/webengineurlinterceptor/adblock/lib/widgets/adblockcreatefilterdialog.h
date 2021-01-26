/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKCREATEFILTERDIALOG_H
#define ADBLOCKCREATEFILTERDIALOG_H

#include "adblockblockableitemswidget.h"

#include <QDialog>
namespace Ui
{
class AdBlockCreateFilterWidget;
}
namespace AdBlock
{
class AdBlockCreateFilterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdBlockCreateFilterDialog(QWidget *parent = nullptr);
    ~AdBlockCreateFilterDialog();

    void setPattern(AdBlockBlockableItemsWidget::TypeElement type, const QString &pattern);

    QString filter() const;

private:
    void slotUpdateFilter();
    enum ElementType { ElementValue = Qt::UserRole + 1 };

    void readConfig();
    void writeConfig();
    void initialize();
    QString mPattern;
    AdBlockBlockableItemsWidget::TypeElement mCurrentType;
    Ui::AdBlockCreateFilterWidget *mUi = nullptr;
};
}

#endif // ADBLOCKCREATEFILTERDIALOG_H
