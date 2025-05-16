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
class QSplitter;
class PIMAUTOGENERATETEXT_TESTS_EXPORT AutogenerateConfigureAskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskWidget(QWidget *parent = nullptr);
    ~AutogenerateConfigureAskWidget() override;

    [[nodiscard]] QList<AutogenerateConfigureAskInfo> askInfos() const;
    void setAskInfos(const QList<AutogenerateConfigureAskInfo> &newAskItems);

private:
    PIMAUTOGENERATETEXT_NO_EXPORT void slotItemChanged(const QModelIndex &current, const QModelIndex &previous);
    QLineEdit *const mSearchLineEdit;
    QPlainTextEdit *const mTextEdit;
    QSplitter *const mSplitter;
    AutogenerateConfigureListView *const mAutogenerateConfigureListView;
};
