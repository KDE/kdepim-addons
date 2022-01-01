/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "liblanguagetool_private_export.h"
#include <QObject>

class LanguageToolComboBox;
class LIBLANGUAGETOOLPRIVATE_TESTS_EXPORT LanguageToolUpdateComboBox : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolUpdateComboBox(QObject *parent = nullptr);
    ~LanguageToolUpdateComboBox() override;

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

