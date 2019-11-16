/*
    Copyright (c) 2015-2019 Montel Laurent <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
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
