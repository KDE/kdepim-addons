/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KContacts/Addressee>
#include <QString>
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
    void setAutoTests(bool b); // Only for autotest

private:
    Q_REQUIRED_RESULT bool loadDomElement(QDomDocument &doc, QFile *file);
    bool mAutoTest = false;
    QWidget *mParentWidget = nullptr;
};
