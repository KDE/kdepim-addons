/*
   Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

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

#include "confirmaddresssimplestringlisteditor.h"
#include "confirmaddressemailentrydialog.h"
#include <KLocalizedString>

#include <QPointer>

ConfirmAddressSimpleStringListEditor::ConfirmAddressSimpleStringListEditor(QWidget *parent, ButtonCode buttons, const QString &addLabel, const QString &removeLabel, const QString &modifyLabel,
                                                                           const QString &addDialogLabel)
    : PimCommon::SimpleStringListEditor(parent, buttons, addLabel, removeLabel, modifyLabel, addDialogLabel)
{
}

void ConfirmAddressSimpleStringListEditor::addNewEntry()
{
    QPointer<ConfirmAddressEmailEntryDialog> dlg = new ConfirmAddressEmailEntryDialog(this);
    dlg->setWindowTitle(i18n("Add Value"));
    if (dlg->exec()) {
        insertNewEntry(dlg->emails());
    }
    delete dlg;
}

QString ConfirmAddressSimpleStringListEditor::modifyEntry(const QString &text)
{
    QString newText;
    QPointer<ConfirmAddressEmailEntryDialog> dlg = new ConfirmAddressEmailEntryDialog(this);
    dlg->setWindowTitle(i18n("Change Value"));
    dlg->setValue(text);
    if (dlg->exec()) {
        newText = dlg->emails();
        Q_EMIT aboutToAdd(newText);
        if (newText == text) {
            newText = QString();
        }
    } else {
        newText = QString();
    }
    delete dlg;
    return newText;
}
