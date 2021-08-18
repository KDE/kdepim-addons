/*
   SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <ImportWizard/AbstractImporter>

class OeImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit OeImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~OeImportData() override;

    Q_REQUIRED_RESULT TypeSupportedOptions supportedOption() override;
    Q_REQUIRED_RESULT bool foundMailer() const override;

    Q_REQUIRED_RESULT bool importMails() override;
    Q_REQUIRED_RESULT QString name() const override;
};

