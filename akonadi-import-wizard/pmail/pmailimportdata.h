/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <ImportWizard/AbstractImporter>

class PMailImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit PMailImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~PMailImportData() override;

    Q_REQUIRED_RESULT TypeSupportedOptions supportedOption() override;
    Q_REQUIRED_RESULT bool foundMailer() const override;

    Q_REQUIRED_RESULT bool importMails() override;
    Q_REQUIRED_RESULT bool importSettings() override;

    Q_REQUIRED_RESULT QString name() const override;
};
