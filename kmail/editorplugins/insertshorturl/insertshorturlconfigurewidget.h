/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef INSERTSHORTURLCONFIGUREWIDGET_H
#define INSERTSHORTURLCONFIGUREWIDGET_H

#include <QWidget>
class QComboBox;
class InsertShorturlConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InsertShorturlConfigureWidget(QWidget *parent = nullptr);
    ~InsertShorturlConfigureWidget();

    void writeConfig();
private:
    void slotChanged();
    void loadConfig();
    bool mChanged = false;
    QComboBox *mShortUrlServer = nullptr;
};

#endif // INSERTSHORTURLCONFIGUREWIDGET_H
