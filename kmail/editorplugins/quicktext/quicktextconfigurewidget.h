/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef QUICKTEXTCONFIGUREWIDGET_H
#define QUICKTEXTCONFIGUREWIDGET_H

#include "quicktext_export.h"
#include <QWidget>
class QuickTextWidget;
class QUICKTEXT_EXPORT QuickTextConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuickTextConfigureWidget(QWidget *parent = nullptr);
    ~QuickTextConfigureWidget() override;
    void save();
    void importQuickText();
    void exportQuickText();

private:
    QuickTextWidget *mSnippetWidget = nullptr;
};

#endif // QUICKTEXTCONFIGUREWIDGET_H
