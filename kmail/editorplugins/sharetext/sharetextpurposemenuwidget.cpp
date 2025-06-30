/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "sharetextpurposemenuwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "sharetextplugineditorinterface.h"
#include <TextCustomEditor/RichTextEditor>
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

#include "moc_sharetextpurposemenuwidget.cpp"
