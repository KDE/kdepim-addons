/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] KContacts::Addressee::List importFile(const QString &fileName);
    void setParentWidget(QWidget *parentWidget);
    void setAutoTests(bool b); // Only for autotest

private:
    [[nodiscard]] bool loadDomElement(QDomDocument &doc, QFile *file);
    bool mAutoTest = false;
    QWidget *mParentWidget = nullptr;
};
