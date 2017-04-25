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

#include "translatorview.h"
#include "translatorwidget.h"

#include <QHBoxLayout>
#include <KLocalizedString>
#include <KToggleAction>
#include <KActionCollection>

TranslatorView::TranslatorView(KActionCollection *ac, QWidget *parent)
    : PimCommon::CustomToolsViewInterface(parent)
    , mAction(nullptr)
    , mTranslatorWidget(nullptr)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    mTranslatorWidget = new PimCommon::TranslatorWidget(this);
    connect(mTranslatorWidget, &PimCommon::TranslatorWidget::toolsWasClosed, this, &TranslatorView::toolsWasClosed);

    layout->addWidget(mTranslatorWidget);
    createAction(ac);
}

TranslatorView::~TranslatorView()
{
}

void TranslatorView::setText(const QString &text)
{
    mTranslatorWidget->setTextToTranslate(text);
}

KToggleAction *TranslatorView::action() const
{
    return mAction;
}

void TranslatorView::slotActivateTranslator(bool state)
{
    if (state) {
        mTranslatorWidget->show();
        Q_EMIT activateView(this);
    } else {
        mTranslatorWidget->hide();
        Q_EMIT activateView(nullptr);
    }
}

void TranslatorView::createAction(KActionCollection *ac)
{
    mAction = new KToggleAction(i18n("&Translator"), this);
    connect(mAction, &KToggleAction::triggered, this, &TranslatorView::slotActivateTranslator);
    if (ac) {
        ac->addAction(QStringLiteral("translator"), mAction);
        ac->setDefaultShortcut(mAction, QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_T));
    }
    mAction->setChecked(false);
}
