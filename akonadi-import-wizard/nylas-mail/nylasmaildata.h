/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef NYLASMAILDATA_H
#define NYLASMAILDATA_H

#include <ImportWizard/AbstractImporter>

class NylasMailImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit NylasMailImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~NylasMailImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    bool importSettings() override;
    bool importAddressBook() override;

    QString name() const override;
};

#endif /* NYLASMAILDATA_H */
