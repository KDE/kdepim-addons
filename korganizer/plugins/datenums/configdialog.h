/*
  This file is part of KOrganizer.

  SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KORG_PLUGINS_DATENUMS_CONFIGDIALOG_H
#define KORG_PLUGINS_DATENUMS_CONFIGDIALOG_H

#include <QDialog>

class QButtonGroup;

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = nullptr);
    ~ConfigDialog() override;

protected:
    void load();
    void save();

protected Q_SLOTS:
    void slotOk();

private:
    QButtonGroup *mDayNumGroup = nullptr;
};

#endif
