/*
    SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kaddressbookmergelib_export.h"
#include "searchduplicateresultwidget.h"
#include <Akonadi/Item>
#include <QTabWidget>

namespace KABMergeContacts
{
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectInformationTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationTabWidget(QWidget *parent = nullptr);
    ~MergeContactSelectInformationTabWidget() override;

    void updateTabWidget();

    Q_REQUIRED_RESULT bool tabBarVisible() const;

    void setRequiresSelectInformationWidgets(const QVector<KABMergeContacts::MergeConflictResult> &list, const Akonadi::Collection &col);

private:
    void addNewWidget(const MergeConflictResult &list, const Akonadi::Collection &col);
};
}
