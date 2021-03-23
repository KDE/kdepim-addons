/*
  This file is part of KAddressBook.
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class QListView;
class QPushButton;
class TemplateSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateSelectionDialog(QWidget *parent = nullptr);

    bool templatesAvailable() const;

    QString selectedTemplate() const;

private:
    void updateButtons();
    QListView *mView = nullptr;
    QPushButton *mOkButton = nullptr;
};

