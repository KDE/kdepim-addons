/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "markdownlib_private_export.h"
#include <MessageComposer/PluginEditorConvertTextConfigureWidget>
class QCheckBox;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownConfigureWidget : public MessageComposer::PluginEditorConvertTextConfigureWidget
{
    Q_OBJECT
public:
    explicit MarkdownConfigureWidget(QWidget *parent = nullptr);
    ~MarkdownConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    QCheckBox *mLatexSupport = nullptr;
    QCheckBox *mExtraDefinitionLists = nullptr;
};

