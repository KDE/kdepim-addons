/*
 * SPDX-FileCopyrightText: 2016 Daniel Vrátil <dvratil@kde.org>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 */

#ifndef SETTINGSCHANGENOTIFIER_H
#define SETTINGSCHANGENOTIFIER_H

#include <QObject>

class SettingsChangeNotifier : public QObject
{
    Q_OBJECT

public:
    static SettingsChangeNotifier *self();

    ~SettingsChangeNotifier();

    void notifySettingsChanged();

Q_SIGNALS:
    void settingsChanged();

private:
    explicit SettingsChangeNotifier(QObject *parent = nullptr);
};

#endif
