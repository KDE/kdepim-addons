/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libkmailmarkdown_export.h"
#include <QDialog>
class MarkdownPreviewWidget;
class LIBKMAILMARKDOWN_EXPORT MarkdownPreviewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MarkdownPreviewDialog(QWidget *parent = nullptr);
    ~MarkdownPreviewDialog() override;
    void setText(const QString &str);

    void setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists);

private:
    void readConfig();
    void writeConfig();
    MarkdownPreviewWidget *const mPreviewWidget;
};
