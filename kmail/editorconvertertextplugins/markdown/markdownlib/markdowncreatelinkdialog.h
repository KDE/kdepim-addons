/*
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATELINKDIALOG_H
#define MARKDOWNCREATELINKDIALOG_H

#include <QDialog>
#include "libkmailmarkdown_export.h"
class MarkdownCreateLinkWidget;
class QPushButton;
class LIBKMAILMARKDOWN_EXPORT MarkdownCreateLinkDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MarkdownCreateLinkDialog(QWidget *parent = nullptr);
    ~MarkdownCreateLinkDialog() override;
    Q_REQUIRED_RESULT QString linkStr() const;
private:
    void writeConfig();
    void readConfig();
    void slotEnabledOkButton(bool enabled);
    MarkdownCreateLinkWidget *mMarkdownCreateLinkWidget = nullptr;
    QPushButton *mOkButton = nullptr;
};

#endif // MARKDOWNCREATELINKDIALOG_H
