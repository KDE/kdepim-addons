/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#include "regexpeditorlineedit.h"
#include <kpluginfactory.h>

#include <QStackedWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <KLocalizedString>
#include <KServiceTypeTrader>
#include <QDialog>
#include <QDebug>
#include <KPluginTrader>

#include <KTextWidgets/kregexpeditorinterface.h>


K_PLUGIN_FACTORY_WITH_JSON(RegexpEditorLineEditFactory, "regexepeditorlineedit.json", registerPlugin<RegexpEditorLineEdit>();
                           )

RegexpEditorLineEdit::RegexpEditorLineEdit(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractRegexpEditorLineEdit(parent)
    , mIsRegExpMode(false)
    , mRegexEditorInstalled(false)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mLineEdit = new QLineEdit(this);
    connect(mLineEdit, &QLineEdit::textChanged, this, &RegexpEditorLineEdit::textChanged);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);

    mRegExpEditorButton = new QPushButton(i18n("..."), this);
    mRegExpEditorButton->setObjectName(QStringLiteral("regexpbutton"));
    mRegExpEditorButton->setToolTip(i18n("Create Regular Expression"));
    mainLayout->addWidget(mRegExpEditorButton);
    mRegexEditorInstalled = !KServiceTypeTrader::self()->query(QStringLiteral("KRegExpEditor/KRegExpEditor")).isEmpty();
    if (mRegexEditorInstalled) {
        connect(mRegExpEditorButton, &QPushButton::clicked, this, &RegexpEditorLineEdit::slotOpenRegexpEditor);
    } else {
        qWarning() << "KRegExpEditor is not installed on system.";
    }
    //Hidden by default
    mRegExpEditorButton->setVisible(false);
}

RegexpEditorLineEdit::~RegexpEditorLineEdit()
{
}

void RegexpEditorLineEdit::slotOpenRegexpEditor()
{
    QDialog *editorDialog = KServiceTypeTrader::createInstanceFromQuery<QDialog>(QStringLiteral("KRegExpEditor/KRegExpEditor"), QString(), this);
    qDebug() << " editorDialog"<<editorDialog;
    if ( editorDialog ) {
        KRegExpEditorInterface* iface = qobject_cast<KRegExpEditorInterface*>(editorDialog);
        Q_ASSERT( iface ); // This should not fail!

        // now use the editor.
        iface->setRegExp(mLineEdit->text());

        if(editorDialog->exec() == QDialog::Accepted) {
            mLineEdit->setText(iface->regExp());
        }
    }
}

void RegexpEditorLineEdit::switchToRegexpEditorLineEdit(bool regexpEditor)
{
    mIsRegExpMode = regexpEditor;
    if (mRegexEditorInstalled) {
        mRegExpEditorButton->setVisible(mIsRegExpMode);
    }
}

void RegexpEditorLineEdit::setCode(const QString &str)
{
    mLineEdit->setText(str);
}

QString RegexpEditorLineEdit::code() const
{
    return mLineEdit->text();
}

#include "regexpeditorlineedit.moc"
