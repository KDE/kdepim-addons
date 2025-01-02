/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "mailmerge_export.h"
#include <QDialog>
class QPushButton;
namespace MailMerge
{
class MailMergeWidget;
class MAILMERGE_EXPORT MailMergeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MailMergeDialog(QWidget *parent = nullptr);
    ~MailMergeDialog() override;

private:
    void slotPreview();
    MailMergeWidget *const mMailMergeWidget;
    QPushButton *const mPreview;
};
}
