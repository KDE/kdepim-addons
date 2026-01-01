/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractImporter>

class OperaImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit OperaImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~OperaImportData() override;

    TypeSupportedOptions supportedOption() override;
    [[nodiscard]] bool foundMailer() const override;

    [[nodiscard]] bool importMails() override;
    [[nodiscard]] bool importAddressBook() override;
    [[nodiscard]] bool importSettings() override;

    [[nodiscard]] QString name() const override;
};
