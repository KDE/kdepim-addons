/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNCONFIGUREDIALOG_H
#define MARKDOWNCONFIGUREDIALOG_H

#include "libkmailmarkdown_export.h"
#include <PimCommon/ConfigurePluginDialog>
class MarkdownConfigureWidget;
class LIBKMAILMARKDOWN_EXPORT MarkdownConfigureDialog : public PimCommon::ConfigurePluginDialog
{
    Q_OBJECT
public:
    explicit MarkdownConfigureDialog(QWidget *parent = nullptr);
    ~MarkdownConfigureDialog() override;

protected:
    QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    MarkdownConfigureWidget *mConfigureWidget = nullptr;
};

#endif // MARKDOWNCONFIGUREDIALOG_H
