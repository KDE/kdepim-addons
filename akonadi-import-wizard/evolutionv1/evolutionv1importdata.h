/*
   Copyright (C) 2012-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#ifndef Evolutionv1ImportData_H
#define Evolutionv1ImportData_H

#include <ImportWizard/AbstractImporter>

class Evolutionv1ImportData : public LibImportWizard::AbstractImporter
{
public:
    explicit Evolutionv1ImportData(QObject *parent, const QList<QVariant> & = QList<QVariant>());
    ~Evolutionv1ImportData();

    TypeSupportedOptions supportedOption() override;
    bool foundMailer() const override;

    bool importMails() override;
    QString name() const override;
};

#endif /* Evolutionv1ImportData_H */
