/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNCONFIGUREWIDGET_H
#define MARKDOWNCONFIGUREWIDGET_H

#include <MessageComposer/PluginEditorConvertTextConfigureWidget>
#include "markdownlib_private_export.h"
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

#endif // MARKDOWNCONFIGUREWIDGET_H
