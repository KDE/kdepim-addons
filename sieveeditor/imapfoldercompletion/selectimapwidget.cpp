/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "selectimapwidget.h"
#include "selectimapfolderdialog.h"
#include <KLineEdit>
#include <KLocalizedString>
#include <QToolButton>
#include <QHBoxLayout>
#include <QPointer>

#include <kpluginfactory.h>
K_PLUGIN_FACTORY_WITH_JSON(ImapFolderCompletionFactory, "imapfoldercompletion.json", registerPlugin<SelectImapWidget>();)

SelectImapWidget::SelectImapWidget(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractMoveImapFolderWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setObjectName(QStringLiteral("mainlayout"));
    layout->setMargin(0);
    mLineEdit = new KLineEdit(this);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    layout->addWidget(mLineEdit);

    mToolButton = new QToolButton(this);
    mToolButton->setText(QStringLiteral("..."));
    mToolButton->setObjectName(QStringLiteral("toolbutton"));
    mToolButton->setToolTip(i18n("Select IMAP folder"));
    layout->addWidget(mToolButton);
    connect(mToolButton, &QToolButton::clicked, this, &SelectImapWidget::slotOpenSelectImapFolder);
}

SelectImapWidget::~SelectImapWidget()
{

}

void SelectImapWidget::setText(const QString &str)
{
    mLineEdit->setText(str);
}

QString SelectImapWidget::text() const
{
    return mLineEdit->text();
}

void SelectImapWidget::setSieveAccount(const KSieveUi::SieveAccount &account)
{
    mAccount = account;
}

void SelectImapWidget::slotOpenSelectImapFolder()
{
    QPointer<SelectImapFolderDialog> dlg = new SelectImapFolderDialog(this);
    dlg->setSieveAccount(mAccount);
    if (dlg->exec()) {
        mLineEdit->setText(dlg->selectedFolderName());
    }
    delete dlg;
}

#include "selectimapwidget.moc"
