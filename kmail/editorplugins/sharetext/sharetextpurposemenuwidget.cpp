/*
   SPDX-FileCopyrightText: 2018-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "sharetextpurposemenuwidget.h"
#include "sharetextplugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
SharetextPurposeMenuWidget::SharetextPurposeMenuWidget(QWidget *parentWidget, QObject *parent)
    : PimCommon::PurposeMenuWidget(parentWidget, parent)
{
}

SharetextPurposeMenuWidget::~SharetextPurposeMenuWidget() = default;

QByteArray SharetextPurposeMenuWidget::text()
{
    if (mInterface) {
        return mInterface->richTextEditor()->toPlainText().toUtf8();
    }
    return {};
}

void SharetextPurposeMenuWidget::setEditorWidget(ShareTextPluginEditorInterface *interface)
{
    mInterface = interface;
}
