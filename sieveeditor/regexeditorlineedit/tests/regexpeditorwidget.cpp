/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "regexpeditorwidget.h"
#include "../regexpeditorlineedit.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QVariant>

RegExpEditorWidget::RegExpEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);
    for (int i = 0; i < 4; ++i) {
        auto switchToRegexp = new QCheckBox(QStringLiteral("Switch to regexp line edit"), this);
        layout->addWidget(switchToRegexp);
        auto lineEdit = new RegexpEditorLineEdit(this);
        layout->addWidget(lineEdit);
        connect(switchToRegexp, &QCheckBox::toggled, lineEdit, &RegexpEditorLineEdit::switchToRegexpEditorLineEdit);
    }

    layout->addStretch(1);
}
