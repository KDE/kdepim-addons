/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "ui_attendeeselector.h"
#include <QDialog>
class QPushButton;

/**
  Dialog to select a set off attendees.
*/
class AttendeeSelector : public QDialog
{
    Q_OBJECT
public:
    explicit AttendeeSelector(QWidget *parent = nullptr);

    [[nodiscard]] QStringList attendees() const;

private:
    void addClicked();
    void removeClicked();
    void textChanged(const QString &text);
    void selectionChanged();
    Ui::AttendeeSelectorWidget ui;
    QPushButton *mOkButton = nullptr;
};
