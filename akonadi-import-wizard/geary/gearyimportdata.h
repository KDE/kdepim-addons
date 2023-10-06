/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <ImportWizard/AbstractImporter>

class GearyImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit GearyImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~GearyImportData() override;

    [[nodiscard]] TypeSupportedOptions supportedOption() override;
    [[nodiscard]] bool foundMailer() const override;

    [[nodiscard]] bool importMails() override;
    [[nodiscard]] bool importSettings() override;
    [[nodiscard]] bool importAddressBook() override;

    [[nodiscard]] QString name() const override;
};
