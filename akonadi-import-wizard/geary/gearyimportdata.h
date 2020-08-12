/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef GearyImportData_H
#define GearyImportData_H

#include <ImportWizard/AbstractImporter>

class GearyImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit GearyImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~GearyImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    bool importSettings() override;
    bool importAddressBook() override;

    QString name() const override;
};

#endif /* TrojiraImportData_H */
