/*
    SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MERGECONTACTSELECTINFORMATIONTABWIDGET_H
#define MERGECONTACTSELECTINFORMATIONTABWIDGET_H

#include <QTabWidget>
#include <AkonadiCore/Item>
#include "kaddressbookmergelib_export.h"
#include "searchduplicateresultwidget.h"

namespace KABMergeContacts {
class KADDRESSBOOKMERGELIB_EXPORT MergeContactSelectInformationTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MergeContactSelectInformationTabWidget(QWidget *parent = nullptr);
    ~MergeContactSelectInformationTabWidget();

    void updateTabWidget();

    Q_REQUIRED_RESULT bool tabBarVisible() const;

    void setRequiresSelectInformationWidgets(const QVector<KABMergeContacts::MergeConflictResult> &list, const Akonadi::Collection &col);
private:
    void addNewWidget(const MergeConflictResult &list, const Akonadi::Collection &col);
};
}
#endif // MERGECONTACTSELECTINFORMATIONTABWIDGET_H
