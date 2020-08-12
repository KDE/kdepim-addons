/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CONFIRMADDRESSSIMPLESTRINGLISTEDITOR_H
#define CONFIRMADDRESSSIMPLESTRINGLISTEDITOR_H
#include <PimCommon/SimpleStringListEditor>

class ConfirmAddressSimpleStringListEditor : public PimCommon::SimpleStringListEditor
{
    Q_OBJECT
public:
    explicit ConfirmAddressSimpleStringListEditor(QWidget *parent = nullptr, ButtonCode buttons = Unsorted, const QString &addLabel = QString(), const QString &removeLabel = QString(), const QString &modifyLabel = QString(), const QString &addDialogLabel = QString());

    void addNewEntry() override;
    Q_REQUIRED_RESULT QString modifyEntry(const QString &text) override;
};

#endif // CONFIRMADDRESSSIMPLESTRINGLISTEDITOR_H
