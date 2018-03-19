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
#include "sieveeditoremaillineditplugin_debug.h"
#include <kpluginfactory.h>
#include <Akonadi/Contact/EmailAddressSelectionDialog>

#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <KLocalizedString>
#include <QDialog>
#include <QTreeView>
#include <KColorScheme>
#include <memory>

K_PLUGIN_CLASS_WITH_JSON(EmailLineEdit, "emaillineedit.json")

EmailLineEdit::EmailLineEdit(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractSelectEmailLineEdit(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mLineEdit = new QLineEdit(this);
    connect(mLineEdit, &QLineEdit::textChanged, this, &EmailLineEdit::slotTextChanged);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);

    mEmailButton = new QToolButton(this);
    mEmailButton->setText(i18n("..."));
    mEmailButton->setObjectName(QStringLiteral("emailbutton"));
    mEmailButton->setToolTip(i18n("Select Emails"));
    mainLayout->addWidget(mEmailButton);
    connect(mEmailButton, &QToolButton::clicked, this, &EmailLineEdit::slotSelectEmail);
    verifyAkonadiStatus();
    connect(Akonadi::ServerManager::self(), &Akonadi::ServerManager::stateChanged, this, &EmailLineEdit::akonadiStateChanged);
}

EmailLineEdit::~EmailLineEdit()
{
}

void EmailLineEdit::akonadiStateChanged(Akonadi::ServerManager::State state)
{
    mEmailButton->setVisible(state == Akonadi::ServerManager::Running);
}

void EmailLineEdit::verifyAkonadiStatus()
{
    Akonadi::ServerManager::State state = Akonadi::ServerManager::self()->state();
    mEmailButton->setVisible(state == Akonadi::ServerManager::Running);
}

void EmailLineEdit::slotSelectEmail()
{
    std::unique_ptr<Akonadi::EmailAddressSelectionDialog> dlg(
        new Akonadi::EmailAddressSelectionDialog(this));
    dlg->setWindowTitle(i18n("Select Emails"));
    dlg->view()->view()->setSelectionMode(QAbstractItemView::SingleSelection);

    if (dlg->exec()) {
        QStringList addresses;
        const Akonadi::EmailAddressSelection::List lstAddress = dlg->selectedAddresses();
        if (!lstAddress.isEmpty()) {
            mLineEdit->setText(lstAddress.constFirst().email());
        }
    }
}

void EmailLineEdit::setText(const QString &str)
{
    mLineEdit->setText(str);
}

QString EmailLineEdit::text() const
{
    return mLineEdit->text();
}

void EmailLineEdit::slotTextChanged()
{
    verifyAddress();
    Q_EMIT valueChanged();
}

void EmailLineEdit::verifyAddress()
{
#ifndef QT_NO_STYLE_STYLESHEET
    QString styleSheet;
    const QString lineEditText = text();
    if (!lineEditText.isEmpty()) {
        const bool incorrectEmail = !lineEditText.contains(QLatin1Char('@'));
        if (mNegativeBackground.isEmpty()) {
            KStatefulBrush bgBrush = KStatefulBrush(KColorScheme::View, KColorScheme::NegativeText);
            mNegativeBackground = QStringLiteral("QLineEdit{ color:%1 }").arg(bgBrush.brush(this).color().name());
        }
        if (incorrectEmail) {
            styleSheet = mNegativeBackground;
        }
    }
    mLineEdit->setStyleSheet(styleSheet);
#endif
}

#include "emaillineedit.moc"
