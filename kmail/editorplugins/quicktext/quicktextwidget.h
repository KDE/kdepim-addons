/*
  SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

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
    enum class EditMode {
        AddSnippet,
        EditSnippet,
        AddGroup,
        EditGroup,
        Unknown,
    };
    void addSnippet();
    void editSnippet();
    void addSnippetGroup();
    void editSnippetGroup();

    void saveAddSnippet();
    void saveEditSnippet();
    void saveAddGroup();
    void saveEditGroup();
    void saveModelIndex(const QModelIndex &index);

    QModelIndex mCurrentGroupIndex;
    EditMode mMode = EditMode::Unknown;

    QuicktextTreeWidget *mTreeWidget = nullptr;
    MailCommon::SnippetWidget *mSnippetWidget = nullptr;
    QuicktextManager *mSnippetsManager = nullptr;
    QStackedWidget *mStackedWidget = nullptr;
    QWidget *mEmptyWidget = nullptr;
};
