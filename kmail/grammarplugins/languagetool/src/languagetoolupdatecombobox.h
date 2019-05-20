/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#ifndef LANGUAGETOOLUPDATECOMBOBOX_H
#define LANGUAGETOOLUPDATECOMBOBOX_H

#include <QObject>
class LanguageToolComboBox;
class LanguageToolUpdateComboBox : public QObject
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
