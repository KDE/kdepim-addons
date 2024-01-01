/*
   SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractImporter>

class PMailImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit PMailImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~PMailImportData() override;

    [[nodiscard]] TypeSupportedOptions supportedOption() override;
    [[nodiscard]] bool foundMailer() const override;

    [[nodiscard]] bool importMails() override;
    [[nodiscard]] bool importSettings() override;

    [[nodiscard]] QString name() const override;
};
