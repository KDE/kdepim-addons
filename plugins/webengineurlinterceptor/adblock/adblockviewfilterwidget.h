/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblockplugin_private_export.h"
#include <QWidget>
namespace TextCustomEditor
{
class RichTextBrowser;
}
class LIBADBLOCKPLUGIN_TESTS_EXPORT AdblockViewFilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdblockViewFilterWidget(QWidget *parent = nullptr);
    ~AdblockViewFilterWidget() override;

    void setFilterText(const QString &str);

private:
    TextCustomEditor::RichTextBrowser *const mRichTextBrowser;
};
