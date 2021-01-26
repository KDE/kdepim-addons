/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTLOSEINFORMATIONWARNING_H
#define MERGECONTACTLOSEINFORMATIONWARNING_H

#include "kaddressbookmergelib_export.h"
#include <KMessageWidget>
namespace KABMergeContacts
{
class KADDRESSBOOKMERGELIB_EXPORT MergeContactLoseInformationWarning : public KMessageWidget
{
    Q_OBJECT
public:
    explicit MergeContactLoseInformationWarning(QWidget *parent = nullptr);
    ~MergeContactLoseInformationWarning() override;

Q_SIGNALS:
    void continueMerging();
    void customizeMergingContacts();

private:
    void slotCustomizeMerge();
    void slotAutomaticMerging();
};
}

#endif // MERGECONTACTLOSEINFORMATIONWARNING_H
