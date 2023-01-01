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

    Q_REQUIRED_RESULT TypeSupportedOptions supportedOption() override;
    Q_REQUIRED_RESULT bool foundMailer() const override;

    Q_REQUIRED_RESULT bool importMails() override;
    Q_REQUIRED_RESULT bool importSettings() override;
    Q_REQUIRED_RESULT bool importAddressBook() override;

    Q_REQUIRED_RESULT QString name() const override;
};
