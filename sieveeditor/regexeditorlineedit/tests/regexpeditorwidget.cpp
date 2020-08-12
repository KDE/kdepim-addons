/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "regexpeditorwidget.h"
#include "../regexpeditorlineedit.h"
#include <QVBoxLayout>
#include <QVariant>
#include <QCheckBox>

RegExpEditorWidget::RegExpEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    for (int i = 0; i < 4; ++i) {
        QCheckBox *switchToRegexp = new QCheckBox(QStringLiteral("Switch to regexp line edit"), this);
        layout->addWidget(switchToRegexp);
        RegexpEditorLineEdit *lineEdit = new RegexpEditorLineEdit(this);
        layout->addWidget(lineEdit);
        connect(switchToRegexp, &QCheckBox::toggled, lineEdit, &RegexpEditorLineEdit::switchToRegexpEditorLineEdit);
    }

    layout->addStretch(1);
}
