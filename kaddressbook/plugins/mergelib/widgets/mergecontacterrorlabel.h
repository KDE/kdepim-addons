/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QLabel>

namespace KABMergeContacts
{
class MergeContactErrorLabel : public QLabel
{
    Q_OBJECT
public:
    enum ErrorType {
        NotEnoughContactsSelected = 0,
        NoContactDuplicatesFound,
        NoContactSelected,
    };
    explicit MergeContactErrorLabel(MergeContactErrorLabel::ErrorType type, QWidget *parent = nullptr);
    ~MergeContactErrorLabel() override;
};
}
