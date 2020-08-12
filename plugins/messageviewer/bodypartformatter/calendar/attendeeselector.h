/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef ATTENDEESELECTOR_H_H
#define ATTENDEESELECTOR_H_H

#include <QDialog>
#include <QPushButton>
#include "ui_attendeeselector.h"

/**
  Dialog to select a set off attendees.
*/
class AttendeeSelector : public QDialog
{
    Q_OBJECT
public:
    explicit AttendeeSelector(QWidget *parent = nullptr);

    QStringList attendees() const;

private:
    void addClicked();
    void removeClicked();
    void textChanged(const QString &text);
    void selectionChanged();
    Ui::AttendeeSelectorWidget ui;
    QPushButton *mOkButton = nullptr;
};

#endif
