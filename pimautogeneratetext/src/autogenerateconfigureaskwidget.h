/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "autogenerateconfigureaskinfo.h"
#include "pimautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
class QPlainTextEdit;
class AutogenerateConfigureListView;
class PIMAUTOGENERATETEXT_TESTS_EXPORT AutogenerateConfigureAskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskWidget(QWidget *parent = nullptr);
    ~AutogenerateConfigureAskWidget() override;

    [[nodiscard]] QList<AutogenerateConfigureAskInfo> askItems() const;
    void setAskItems(const QList<AutogenerateConfigureAskInfo> &newAskItems);

private:
    void slotClicked(const QModelIndex &index);
    QLineEdit *const mSearchLineEdit;
    QPlainTextEdit *const mTextEdit;
    AutogenerateConfigureListView *const mAutogenerateConfigureListView;
};
