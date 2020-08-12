/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNPREVIEWDIALOG_H
#define MARKDOWNPREVIEWDIALOG_H

#include <QDialog>
#include "libkmailmarkdown_export.h"
class MarkdownPreviewWidget;
class LIBKMAILMARKDOWN_EXPORT MarkdownPreviewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MarkdownPreviewDialog(QWidget *parent = nullptr);
    ~MarkdownPreviewDialog();
    void setText(const QString &str);

    void setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists);
private:
    void readConfig();
    void writeConfig();
    MarkdownPreviewWidget *mPreviewWidget = nullptr;
};

#endif // MARKDOWNPREVIEWDIALOG_H
