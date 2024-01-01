/*
   SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <ImportWizard/AbstractImporter>

class OeImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit OeImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~OeImportData() override;

    [[nodiscard]] TypeSupportedOptions supportedOption() override;
    [[nodiscard]] bool foundMailer() const override;

    [[nodiscard]] bool importMails() override;
    [[nodiscard]] QString name() const override;
};
