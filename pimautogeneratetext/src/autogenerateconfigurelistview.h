/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "pimautogeneratetext_private_export.h"
#include <QListView>
class AutogenerateConfigureAskModel;
class PIMAUTOGENERATETEXT_TESTS_EXPORT AutogenerateConfigureListView : public QListView
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureListView(QWidget *parent = nullptr);
    ~AutogenerateConfigureListView() override;

private:
    AutogenerateConfigureAskModel *const mModel;
};
