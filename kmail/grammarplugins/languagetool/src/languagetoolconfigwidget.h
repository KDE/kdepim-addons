/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLCONFIGWIDGET_H
#define LANGUAGETOOLCONFIGWIDGET_H

#include <QWidget>
#include "libkmaillanguagetool_export.h"
class QCheckBox;
class QLineEdit;
class QLabel;
class LanguageToolComboBox;
class LanguageToolUpdateComboBox;
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
    void updateWidgets(bool enabled);
    QCheckBox *mUseLocalInstance = nullptr;
    QLineEdit *mInstancePath = nullptr;
    QLabel *mInstancePathLabel = nullptr;
    LanguageToolComboBox *mLanguageToolCombobox = nullptr;
    LanguageToolUpdateComboBox *mLanguageToolUpdateCombobox = nullptr;
};

#endif // LANGUAGETOOLCONFIGWIDGET_H
