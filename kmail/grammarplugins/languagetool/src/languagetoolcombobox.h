/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLCOMBOBOX_H
#define LANGUAGETOOLCOMBOBOX_H

#include "libkmaillanguagetool_export.h"
#include <QComboBox>
class LanguageInfo;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit LanguageToolComboBox(QWidget *parent = nullptr);
    ~LanguageToolComboBox() override;

    void setLanguage(const QString &str);
    Q_REQUIRED_RESULT QString language() const;

    void fillComboBox(const QVector<LanguageInfo> &info);

private:
    void fillComboBox();
    Q_DISABLE_COPY(LanguageToolComboBox)
};

#endif // LANGUAGETOOLCOMBOBOX_H
