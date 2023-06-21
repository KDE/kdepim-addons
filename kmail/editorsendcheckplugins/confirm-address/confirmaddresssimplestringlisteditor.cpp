/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "confirmaddresssimplestringlisteditor.h"
#include "confirmaddressemailentrydialog.h"
#include <KLocalizedString>

#include <QPointer>

ConfirmAddressSimpleStringListEditor::ConfirmAddressSimpleStringListEditor(QWidget *parent,
                                                                           ButtonCode buttons,
                                                                           const QString &addLabel,
                                                                           const QString &removeLabel,
                                                                           const QString &modifyLabel,
                                                                           const QString &addDialogLabel)
    : PimCommon::SimpleStringListEditor(parent, buttons, addLabel, removeLabel, modifyLabel, addDialogLabel)
{
}

void ConfirmAddressSimpleStringListEditor::addNewEntry()
{
    QPointer<ConfirmAddressEmailEntryDialog> dlg = new ConfirmAddressEmailEntryDialog(this);
    dlg->setWindowTitle(i18nc("@title:window", "Add Value"));
    if (dlg->exec()) {
        insertNewEntry(dlg->emails());
    }
    delete dlg;
}

QString ConfirmAddressSimpleStringListEditor::modifyEntry(const QString &text)
{
    QString newText;
    QPointer<ConfirmAddressEmailEntryDialog> dlg = new ConfirmAddressEmailEntryDialog(this);
    dlg->setWindowTitle(i18nc("@title:window", "Change Value"));
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

#include "moc_confirmaddresssimplestringlisteditor.cpp"
