/*
   SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef MailAppImportData_H
#define MailAppImportData_H

#include <ImportWizard/AbstractImporter>

class MailAppImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit MailAppImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~MailAppImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    QString name() const override;
};

#endif /* MailApp ImportData_H */
