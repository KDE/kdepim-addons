/*
   SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <ImportWizard/AbstractImporter>

class TheBatImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit TheBatImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~TheBatImportData() override;

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    QString name() const override;
};

