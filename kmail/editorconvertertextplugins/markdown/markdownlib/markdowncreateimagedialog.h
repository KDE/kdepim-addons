/*
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATEIMAGEDIALOG_H
#define MARKDOWNCREATEIMAGEDIALOG_H

#include <QDialog>
#include "libkmailmarkdown_export.h"
class MarkdownCreateImageWidget;
class QPushButton;
class LIBKMAILMARKDOWN_EXPORT MarkdownCreateImageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MarkdownCreateImageDialog(QWidget *parent = nullptr);
    ~MarkdownCreateImageDialog() override;
    Q_REQUIRED_RESULT QString linkStr() const;
private:
    void writeConfig();
    void readConfig();
    void slotEnabledOkButton(bool enabled);
    MarkdownCreateImageWidget *mMarkdownCreateImageWidget = nullptr;
    QPushButton *mOkButton = nullptr;
};

#endif // MARKDOWNCREATEIMAGEDIALOG_H
