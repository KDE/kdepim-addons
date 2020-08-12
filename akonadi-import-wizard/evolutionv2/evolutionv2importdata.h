/*
   SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef Evolutionv2ImportData_H
#define Evolutionv2ImportData_H

#include <ImportWizard/AbstractImporter>
class Evolutionv2ImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit Evolutionv2ImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~Evolutionv2ImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    QString name() const override;
};

#endif /* Evolutionv2ImportData_H */
