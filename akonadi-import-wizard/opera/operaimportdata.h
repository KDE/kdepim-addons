/*
   SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef OperaImportData_H
#define OperaImportData_H

#include <ImportWizard/AbstractImporter>

class OperaImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit OperaImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~OperaImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    bool importAddressBook() override;
    bool importSettings() override;

    QString name() const override;
};

#endif /* OperaImportData_H */
