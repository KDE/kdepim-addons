/*
  SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "quicktext_export.h"
#include <QModelIndex>
#include <QWidget>
class QuicktextTreeWidget;
namespace MailCommon
{
class SnippetWidget;
}
class QuicktextManager;
class QStackedWidget;
class QUICKTEXT_EXPORT QuickTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QuickTextWidget(QWidget *parent = nullptr);
    ~QuickTextWidget() override;

    void save();
    void importQuickText();
    void exportQuickText();

private:
    enum class EditMode : uint8_t {
        AddSnippet,
        EditSnippet,
        AddGroup,
        EditGroup,
        Unknown,
    };
    QUICKTEXT_NO_EXPORT void addSnippet();
    QUICKTEXT_NO_EXPORT void editSnippet();
    QUICKTEXT_NO_EXPORT void addSnippetGroup();
    QUICKTEXT_NO_EXPORT void editSnippetGroup();

    QUICKTEXT_NO_EXPORT void saveAddSnippet();
    QUICKTEXT_NO_EXPORT void saveEditSnippet();
    QUICKTEXT_NO_EXPORT void saveAddGroup();
    QUICKTEXT_NO_EXPORT void saveEditGroup();
    QUICKTEXT_NO_EXPORT void saveModelIndex(const QModelIndex &index);

    QModelIndex mCurrentGroupIndex;
    EditMode mMode = EditMode::Unknown;

    QuicktextTreeWidget *mTreeWidget = nullptr;
    MailCommon::SnippetWidget *mSnippetWidget = nullptr;
    QuicktextManager *mSnippetsManager = nullptr;
    QStackedWidget *mStackedWidget = nullptr;
    QWidget *mEmptyWidget = nullptr;
};
