/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAMMALECTERESULTWIDGET_H
#define GRAMMALECTERESULTWIDGET_H

#include "grammarresultwidget.h"
#include "libkmailgrammalecte_export.h"
#include "grammalectegrammarerror.h"
#include "grammalecteresultjob.h"
namespace MessageComposer {
}
class GrammalecteResultJob;
class LIBKMAILGRAMMALECTE_EXPORT GrammalecteResultWidget : public GrammarResultWidget
{
    Q_OBJECT
public:
    explicit GrammalecteResultWidget(QWidget *parent = nullptr);
    ~GrammalecteResultWidget() override;
    void checkGrammar() override;
private:
    void slotCheckGrammarFinished(const QString &result);
    void slotError(GrammalecteResultJob::ErrorType error);
};

#endif // GRAMMALECTERESULTWIDGET_H
