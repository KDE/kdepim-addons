/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginaiwidget.h"
#include <KLocalizedString>
#include <QStyle>
#include <QToolButton>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateQuickAskWidget>
using namespace Qt::Literals::StringLiterals;
ViewerPluginAIWidget::ViewerPluginAIWidget(QWidget *parent)
    : QWidget{parent}
    , mCloseButton(new QToolButton(this))
{
    auto layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins({});

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setSpacing(style()->pixelMetric(QStyle::PM_LayoutHorizontalSpacing));
    hboxLayout->setContentsMargins(style()->pixelMetric(QStyle::PM_LayoutLeftMargin),
                                   style()->pixelMetric(QStyle::PM_LayoutTopMargin),
                                   style()->pixelMetric(QStyle::PM_LayoutRightMargin),
                                   style()->pixelMetric(QStyle::PM_LayoutBottomMargin));
    mCloseButton->setObjectName(u"close-button"_s);
    mCloseButton->setIcon(QIcon::fromTheme(u"dialog-close"_s));
    mCloseButton->setIconSize(QSize(16, 16));
    mCloseButton->setToolTip(i18nc("@info:tooltip", "Close"));

#ifndef QT_NO_ACCESSIBILITY
    mCloseButton->setAccessibleName(i18n("Close"));
#endif
    mCloseButton->setAutoRaise(true);
    hboxLayout->addWidget(mCloseButton);
    connect(mCloseButton, &QToolButton::clicked, this, &ViewerPluginAIWidget::slotCloseWidget);
}

ViewerPluginAIWidget::~ViewerPluginAIWidget() = default;

void ViewerPluginAIWidget::slotCloseWidget()
{
    if (isHidden()) {
        return;
    }
    hide();
    // TODO Q_EMIT toolsWasClosed();
}

#include "moc_viewerpluginaiwidget.cpp"
