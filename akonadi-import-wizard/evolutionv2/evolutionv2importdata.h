/*
   SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

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

