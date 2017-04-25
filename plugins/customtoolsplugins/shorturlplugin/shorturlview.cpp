/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

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

#include "shorturlview.h"
#include <KToggleAction>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <kactioncollection.h>
#include <shorturl/shorturlwidgetng.h>

using namespace PimCommon;

ShorturlView::ShorturlView(KActionCollection *ac, QWidget *parent)
    : CustomToolsViewInterface(parent)
    , mAction(nullptr)
    , mShorturl(nullptr)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    createAction(ac);
    mShorturl = new ShortUrlWidgetNg(this);
    connect(mShorturl, &ShortUrlWidgetNg::toolsWasClosed, this, &ShorturlView::toolsWasClosed);
    connect(mShorturl, &ShortUrlWidgetNg::insertText, this, &ShorturlView::insertText);

    layout->addWidget(mShorturl);
}

ShorturlView::~ShorturlView()
{
}

KToggleAction *ShorturlView::action() const
{
    return mAction;
}

void ShorturlView::createAction(KActionCollection *ac)
{
    mAction = new KToggleAction(i18n("Generate Shortened URL"), this);
    connect(mAction, &KToggleAction::triggered, this, &ShorturlView::slotActivateShorturl);
    if (ac) {
        ac->addAction(QStringLiteral("shorten_url"), mAction);
    }
    mAction->setChecked(false);
}

void ShorturlView::slotActivateShorturl(bool state)
{
    if (state) {
        mShorturl->show();
        Q_EMIT activateView(this);
    } else {
        mShorturl->hide();
        Q_EMIT activateView(nullptr);
    }
}
