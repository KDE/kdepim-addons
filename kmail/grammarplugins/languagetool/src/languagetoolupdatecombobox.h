/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLUPDATECOMBOBOX_H
#define LANGUAGETOOLUPDATECOMBOBOX_H

#include <QObject>
#include "liblanguagetool_private_export.h"

class LanguageToolComboBox;
class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageToolUpdateComboBox : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolUpdateComboBox(QObject *parent = nullptr);
    ~LanguageToolUpdateComboBox();

    LanguageToolComboBox *languageToolCombobox() const;
    void setLanguageToolCombobox(LanguageToolComboBox *languageToolCombobox);

    void checkListOfLanguagesFromSpecificPath(const QString &url);
    void refreshListOfLanguages();

    QWidget *parentWidget() const;
    void setParentWidget(QWidget *parentWidget);

private:
    void slotGetLanguagesFinished(const QString &result);
    void slotGetLanguagesError(const QString &error);
    LanguageToolComboBox *mLanguageToolCombobox = nullptr;
    QWidget *mParentWidget = nullptr;
};

#endif // LANGUAGETOOLUPDATECOMBOBOX_H
