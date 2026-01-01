/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <PimCommon/SimpleStringListEditor>

class ConfirmAddressSimpleStringListEditor : public PimCommon::SimpleStringListEditor
{
    Q_OBJECT
public:
    explicit ConfirmAddressSimpleStringListEditor(QWidget *parent = nullptr,
                                                  ButtonCode buttons = Unsorted,
                                                  const QString &addLabel = QString(),
                                                  const QString &removeLabel = QString(),
                                                  const QString &modifyLabel = QString(),
                                                  const QString &addDialogLabel = QString());

    void addNewEntry() override;
    [[nodiscard]] QString modifyEntry(const QString &text) override;
};
