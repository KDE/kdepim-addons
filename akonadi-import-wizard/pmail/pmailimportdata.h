/*
   SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractImporter>

class PMailImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit PMailImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~PMailImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    bool importSettings() override;

    QString name() const override;
};

