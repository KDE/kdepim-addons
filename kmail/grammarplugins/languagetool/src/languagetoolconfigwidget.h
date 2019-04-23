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

#ifndef LANGUAGETOOLCONFIGWIDGET_H
#define LANGUAGETOOLCONFIGWIDGET_H

#include <QWidget>
#include "libkmaillanguagetool_export.h"
class QCheckBox;
class QLineEdit;
class QLabel;
class LanguageToolComboBox;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LanguageToolConfigWidget(QWidget *parent = nullptr);
    ~LanguageToolConfigWidget();
    void loadSettings();
    void saveSettings();
private:
    Q_DISABLE_COPY(LanguageToolConfigWidget)
    void uploadListOfLanguages();
    void slotGetLanguagesError(const QString &error);
    void slotGetLanguagesFinished(const QString &result);
    void refreshListOfLanguages();
    void updateWidgets(bool enabled);
    QCheckBox *mUseLocalInstance = nullptr;
    QLineEdit *mInstancePath = nullptr;
    QLabel *mInstancePathLabel = nullptr;
    LanguageToolComboBox *mLanguageToolCombobox = nullptr;
};

#endif // LANGUAGETOOLCONFIGWIDGET_H
