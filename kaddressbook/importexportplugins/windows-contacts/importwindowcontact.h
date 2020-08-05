/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

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

#ifndef IMPORTCONTACTEXPORT_H
#define IMPORTCONTACTEXPORT_H

#include <QString>
class QDomDocument;
class QFile;
class QWidget;
class ImportWindowContact
{
public:
    ImportWindowContact();
    ~ImportWindowContact();

    void importFile(const QString &fileName);
    void setParentWidget(QWidget *parentWidget);

private:
    Q_REQUIRED_RESULT bool loadDomElement(QDomDocument &doc, QFile *file);
    QWidget *mParentWidget = nullptr;
};

#endif // IMPORTCONTACTEXPORT_H
