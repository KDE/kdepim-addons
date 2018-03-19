/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#include "emaillineedit.h"
#include "regexpeditorlineeditplugin_debug.h"
#include <kpluginfactory.h>

#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <KLocalizedString>
#include <KServiceTypeTrader>
#include <QDialog>

#include <KTextWidgets/kregexpeditorinterface.h>

K_PLUGIN_CLASS_WITH_JSON(EmailLineEdit, "emaillineedit.json")

EmailLineEdit::EmailLineEdit(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractSelectEmailLineEdit(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mLineEdit = new QLineEdit(this);
    //FIXME connect(mLineEdit, &QLineEdit::textChanged, this, &EmailLineEdit::textChanged);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);

    mEmailButton = new QToolButton(this);
    mEmailButton->setText(i18n("..."));
    mEmailButton->setObjectName(QStringLiteral("emailbutton"));
    mEmailButton->setToolTip(i18n("Select Emails"));
    mainLayout->addWidget(mEmailButton);
}

EmailLineEdit::~EmailLineEdit()
{
}

void EmailLineEdit::setText(const QString &str)
{
    mLineEdit->setText(str);
}

QString EmailLineEdit::text() const
{
    return mLineEdit->text();
}

#include "emaillineedit.moc"
