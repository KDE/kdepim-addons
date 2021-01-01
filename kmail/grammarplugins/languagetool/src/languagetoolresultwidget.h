/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUAGETOOLRESULTWIDGET_H
#define LANGUAGETOOLRESULTWIDGET_H

#include "grammarresultwidget.h"
#include "libkmaillanguagetool_export.h"
#include "languagetoolgrammarerror.h"
namespace MessageComposer {
}
class LanguageToolComboBox;
class LanguageToolUpdateComboBox;
class LIBKMAILLANGUAGETOOL_EXPORT LanguageToolResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    explicit LanguageToolResultWidget(QWidget *parent = nullptr);
    ~LanguageToolResultWidget() override;
    void checkGrammar() override;

protected:
    void addExtraWidget() override;

private:
    Q_DISABLE_COPY(LanguageToolResultWidget)
    void slotCheckGrammarFinished(const QString &result);
    void slotError(const QString &str);
    LanguageToolComboBox *mLanguageToolComboBox = nullptr;
    LanguageToolUpdateComboBox *mLanguageToolUpdateCombobox = nullptr;
};

#endif // LANGUAGETOOLRESULTWIDGET_H
