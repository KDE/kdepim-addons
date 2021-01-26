/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTERRORLABEL_H
#define MERGECONTACTERRORLABEL_H

#include <QLabel>

namespace KABMergeContacts
{
class MergeContactErrorLabel : public QLabel
{
    Q_OBJECT
public:
    enum ErrorType { NotEnoughContactsSelected = 0, NoContactDuplicatesFound, NoContactSelected };
    explicit MergeContactErrorLabel(MergeContactErrorLabel::ErrorType type, QWidget *parent = nullptr);
    ~MergeContactErrorLabel() override;
};
}

#endif // MERGECONTACTERRORLABEL_H
