/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "markdownlib_private_export.h"
#include <MessageComposer/PluginEditorConfigureBaseWidget>
class QCheckBox;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownConfigureWidget : public MessageComposer::PluginEditorConfigureBaseWidget
{
    Q_OBJECT
public:
    explicit MarkdownConfigureWidget(QWidget *parent = nullptr);
    ~MarkdownConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    QCheckBox *const mLatexSupport;
    QCheckBox *const mExtraDefinitionLists;
};
