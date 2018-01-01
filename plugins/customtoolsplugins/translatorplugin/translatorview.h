/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

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

#ifndef TRANSLATORVIEW_H
#define TRANSLATORVIEW_H

#include <pimcommon/customtoolsviewinterface.h>
class KActionCollection;
namespace PimCommon {
class TranslatorWidget;
}
class TranslatorView : public PimCommon::CustomToolsViewInterface
{
    Q_OBJECT
public:
    explicit TranslatorView(KActionCollection *ac, QWidget *parent);
    ~TranslatorView();
    KToggleAction *action() const override;

    void setText(const QString &text) override;
private:
    void slotActivateTranslator(bool state);
    void createAction(KActionCollection *ac);
    KToggleAction *mAction = nullptr;
    PimCommon::TranslatorWidget *mTranslatorWidget = nullptr;
};
#endif // TRANSLATORVIEW_H
