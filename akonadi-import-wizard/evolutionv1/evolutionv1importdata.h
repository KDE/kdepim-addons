/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <ImportWizard/AbstractImporter>

class Evolutionv1ImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit Evolutionv1ImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~Evolutionv1ImportData() override;

    [[nodiscard]] TypeSupportedOptions supportedOption() override;
    [[nodiscard]] bool foundMailer() const override;

    [[nodiscard]] bool importMails() override;
    [[nodiscard]] QString name() const override;
};
