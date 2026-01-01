/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontacterrorlabel.h"
#include <KLocalizedString>

using namespace KABMergeContacts;
MergeContactErrorLabel::MergeContactErrorLabel(ErrorType type, QWidget *parent)
    : QLabel(parent)
{
    QFont font;
    font.setBold(true);
    switch (type) {
    case NotEnoughContactsSelected:
        setText(i18n("You must select at least two elements."));
        break;
    case NoContactDuplicatesFound:
        setText(i18n("No duplicated contact found."));
        break;
    case NoContactSelected:
        setText(i18n("No contacts selected."));
        break;
    }

    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setFont(font);
}

MergeContactErrorLabel::~MergeContactErrorLabel() = default;

#include "moc_mergecontacterrorlabel.cpp"
