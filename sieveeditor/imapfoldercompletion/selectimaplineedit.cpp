/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "selectimaplineedit.h"
#include "selectimaplineeditcompletermodel.h"
#include <QCompleter>
#include <QAbstractProxyModel>
//#define COMPLETION_LINE_EDIT 1
SelectImapLineEdit::SelectImapLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , mCompleter(nullptr)
{
}

SelectImapLineEdit::~SelectImapLineEdit()
{
}

void SelectImapLineEdit::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)
{
    //TODO FIXME
#ifdef COMPLETION_LINE_EDIT
    delete mCompleter;
    mCompleter = new QCompleter(this);
    SelectImapLineEditCompleterModel *model = new SelectImapLineEditCompleterModel(account, this);
    mCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    mCompleter->setModel(model->completerModel());
    setCompleter(mCompleter);
#else
    Q_UNUSED(account);
#endif
}
