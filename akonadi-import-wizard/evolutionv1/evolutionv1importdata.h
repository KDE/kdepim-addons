/*
   SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#ifndef Evolutionv1ImportData_H
#define Evolutionv1ImportData_H

#include <ImportWizard/AbstractImporter>

class Evolutionv1ImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit Evolutionv1ImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~Evolutionv1ImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    QString name() const override;
};

#endif /* Evolutionv1ImportData_H */
