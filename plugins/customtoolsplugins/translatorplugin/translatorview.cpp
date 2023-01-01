/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorview.h"
#include <PimCommonTextTranslator/TranslatorWidget>

#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>
#include <QHBoxLayout>

TranslatorView::TranslatorView(KActionCollection *ac, QWidget *parent)
    : PimCommon::CustomToolsViewInterface(parent)
    , mTranslatorWidget(new PimCommonTextTranslator::TranslatorWidget(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins({});
    connect(mTranslatorWidget, &PimCommonTextTranslator::TranslatorWidget::toolsWasClosed, this, &TranslatorView::toolsWasClosed);

    layout->addWidget(mTranslatorWidget);
    createAction(ac);
}

TranslatorView::~TranslatorView() = default;

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
        ac->setDefaultShortcut(mAction, QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_T));
    }
    mAction->setChecked(false);
}
