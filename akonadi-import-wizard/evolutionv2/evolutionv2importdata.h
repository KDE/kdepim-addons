/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <ImportWizard/AbstractImporter>
class Evolutionv2ImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit Evolutionv2ImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~Evolutionv2ImportData() override;

    [[nodiscard]] TypeSupportedOptions supportedOption() override;
    [[nodiscard]] bool foundMailer() const override;

    [[nodiscard]] bool importMails() override;
    [[nodiscard]] QString name() const override;
};
