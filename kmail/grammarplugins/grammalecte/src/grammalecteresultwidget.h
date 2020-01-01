/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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
