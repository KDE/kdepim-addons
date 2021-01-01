/*
   SPDX-FileCopyrightText: 2020-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef IMPORTCONTACTEXPORT_H
#define IMPORTCONTACTEXPORT_H

#include <QString>
#include <KContacts/Addressee>
class QDomDocument;
class QFile;
class QWidget;
class ImportWindowContact
{
public:
    ImportWindowContact();
    ~ImportWindowContact();

    Q_REQUIRED_RESULT KContacts::Addressee::List importFile(const QString &fileName);
    void setParentWidget(QWidget *parentWidget);
    void setAutoTests(bool b); //Only for autotest

private:
    Q_REQUIRED_RESULT bool loadDomElement(QDomDocument &doc, QFile *file);
    bool mAutoTest = false;
    QWidget *mParentWidget = nullptr;
};

#endif // IMPORTCONTACTEXPORT_H
