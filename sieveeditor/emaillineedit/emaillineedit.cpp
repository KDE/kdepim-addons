/*
   Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

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
#include "regexpeditorlineeditplugin_debug.h"
#include <kpluginfactory.h>

#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <KLocalizedString>
#include <KServiceTypeTrader>
#include <QDialog>

#include <KTextWidgets/kregexpeditorinterface.h>

K_PLUGIN_CLASS_WITH_JSON(RegexpEditorLineEdit, "regexepeditorlineedit.json")
struct InfoRegExp
{
    InfoRegExp()
        : status(Unknown)
        , mEditorDialog(nullptr)
    {
    }

    enum RegexpEditorStatus {
        Unknown = 0,
        Installed,
        NotInstalled
    };
    RegexpEditorStatus status;
    QDialog *mEditorDialog = nullptr;
};

Q_GLOBAL_STATIC(InfoRegExp, s_regexpeditorinstalled)

RegexpEditorLineEdit::RegexpEditorLineEdit(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractRegexpEditorLineEdit(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mLineEdit = new QLineEdit(this);
    connect(mLineEdit, &QLineEdit::textChanged, this, &RegexpEditorLineEdit::textChanged);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);

    mRegExpEditorButton = new QToolButton(this);
    mRegExpEditorButton->setText(i18n("..."));
    mRegExpEditorButton->setObjectName(QStringLiteral("regexpbutton"));
    mRegExpEditorButton->setToolTip(i18n("Create Regular Expression"));
    mainLayout->addWidget(mRegExpEditorButton);
    if (s_regexpeditorinstalled->status == InfoRegExp::Unknown) {
        if (KServiceTypeTrader::self()->query(QStringLiteral("KRegExpEditor/KRegExpEditor")).isEmpty()) {
            s_regexpeditorinstalled->status = InfoRegExp::NotInstalled;
        } else {
            s_regexpeditorinstalled->status = InfoRegExp::Installed;
        }
    }
    if (s_regexpeditorinstalled->status == InfoRegExp::Installed) {
        connect(mRegExpEditorButton, &QToolButton::clicked, this, &RegexpEditorLineEdit::slotOpenRegexpEditor);
    } else {
        qCWarning(REGEXPEDITORLINEEDITPLUGIN_LOG) << "KRegExpEditor is not installed on system.";
    }
    //Hidden by default
    mRegExpEditorButton->setVisible(false);
}

RegexpEditorLineEdit::~RegexpEditorLineEdit()
{
}

void RegexpEditorLineEdit::slotOpenRegexpEditor()
{
    if (!s_regexpeditorinstalled->mEditorDialog) {
        QString error;

        s_regexpeditorinstalled->mEditorDialog = KServiceTypeTrader::createInstanceFromQuery<QDialog>(QStringLiteral("KRegExpEditor/KRegExpEditor"), this, this, {}, {}, &error);
        if (!s_regexpeditorinstalled->mEditorDialog) {
            qCWarning(REGEXPEDITORLINEEDITPLUGIN_LOG) << " Impossible to create regexpeditor " << error;
            return;
        }
    }
    KRegExpEditorInterface *iface = qobject_cast<KRegExpEditorInterface *>(s_regexpeditorinstalled->mEditorDialog);
    Q_ASSERT(iface);   // This should not fail!

    // now use the editor.
    iface->setRegExp(mLineEdit->text());

    if (s_regexpeditorinstalled->mEditorDialog->exec() == QDialog::Accepted) {
        mLineEdit->setText(iface->regExp());
    }
}

void RegexpEditorLineEdit::switchToRegexpEditorLineEdit(bool regexpEditor)
{
    if (s_regexpeditorinstalled->status == InfoRegExp::Installed) {
        mRegExpEditorButton->setVisible(regexpEditor);
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

void RegexpEditorLineEdit::setClearButtonEnabled(bool b)
{
    mLineEdit->setClearButtonEnabled(b);
}

void RegexpEditorLineEdit::setPlaceholderText(const QString &str)
{
    mLineEdit->setPlaceholderText(str);
}

#include "regexpeditorlineedit.moc"
