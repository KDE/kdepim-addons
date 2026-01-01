/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <ImportWizard/AbstractImporter>

class TheBatImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit TheBatImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~TheBatImportData() override;

    [[nodiscard]] TypeSupportedOptions supportedOption() override;
    [[nodiscard]] bool foundMailer() const override;

    [[nodiscard]] bool importMails() override;
    [[nodiscard]] QString name() const override;
};
