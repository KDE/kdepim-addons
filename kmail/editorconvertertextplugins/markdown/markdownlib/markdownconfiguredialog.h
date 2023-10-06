/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
    [[nodiscard]] QWidget *createLayout() override;
    void save() override;
    void load() override;
    void reset() override;
    void help() override;

private:
    MarkdownConfigureWidget *mConfigureWidget = nullptr;
};
