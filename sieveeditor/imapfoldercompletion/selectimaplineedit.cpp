/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimaplineedit.h"
#include "selectimaplineeditcompletermodel.h"
#include <QCompleter>
//#define COMPLETION_LINE_EDIT 1
SelectImapLineEdit::SelectImapLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , mCompleter(nullptr)
{
    setClearButtonEnabled(true);
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
