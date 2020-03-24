/*
   Copyright (C) 2018-2020 Laurent Montel <montel@kde.org>

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
#include <KPluginFactory>
#include <Akonadi/Contact/EmailAddressSelectionDialog>

#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <KLocalizedString>
#include <QTreeView>
#include <KColorScheme>
#include <memory>
#include <KPluginLoader>

K_PLUGIN_CLASS_WITH_JSON(EmailLineEdit, "emaillineedit.json")

EmailLineEdit::EmailLineEdit(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractSelectEmailLineEdit(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mLineEdit = new QLineEdit(this);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mLineEdit->setClearButtonEnabled(true);
    mLineEdit->setPlaceholderText(i18n("Click on button for selecting contacts..."));
    connect(mLineEdit, &QLineEdit::textChanged, this, &EmailLineEdit::slotTextChanged);
    mainLayout->addWidget(mLineEdit);

    mEmailButton = new QToolButton(this);
    mEmailButton->setText(i18n("..."));
    mEmailButton->setObjectName(QStringLiteral("emailbutton"));
    mEmailButton->setToolTip(i18n("Select Emails"));
    mainLayout->addWidget(mEmailButton);
    connect(mEmailButton, &QToolButton::clicked, this, &EmailLineEdit::slotSelectEmail);
    verifyAkonadiStatus();
    connect(Akonadi::ServerManager::self(), &Akonadi::ServerManager::stateChanged, this, &EmailLineEdit::akonadiStateChanged);
    verifyAddress();
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

void EmailLineEdit::insertAddresses(const KContacts::Addressee::List &list)
{
    QString currentText = mLineEdit->text();
    bool firstElement = currentText.isEmpty();
    for (const KContacts::Addressee &contact : list) {
        if (!firstElement) {
            currentText.append(QLatin1Char(';'));
        } else {
            firstElement = false;
        }
        currentText.append(contact.preferredEmail());
    }
    mLineEdit->setText(currentText);
}

void EmailLineEdit::slotSelectEmail()
{
    std::unique_ptr<Akonadi::AbstractEmailAddressSelectionDialog> dlg;
    KPluginLoader loader(QStringLiteral("akonadi/emailaddressselectionldapdialogplugin"));
    KPluginFactory *factory = loader.factory();
    if (factory) {
        dlg.reset(factory->create<Akonadi::AbstractEmailAddressSelectionDialog>(this));
    } else {
        dlg.reset(new Akonadi::EmailAddressSelectionDialog(this));
    }
    dlg->setWindowTitle(i18nc("@title:window", "Select Emails"));
    dlg->view()->view()->setSelectionMode(multiSelection() ? QAbstractItemView::MultiSelection : QAbstractItemView::SingleSelection);
    connect(dlg.get(), &Akonadi::AbstractEmailAddressSelectionDialog::insertAddresses, this, &EmailLineEdit::insertAddresses);
    if (dlg->exec()) {
        const Akonadi::EmailAddressSelection::List lstAddress = dlg->selectedAddresses();
        if (!lstAddress.isEmpty()) {
            bool firstElement = true;
            QString result;
            for (const Akonadi::EmailAddressSelection &value : lstAddress) {
                if (!firstElement) {
                    result.append(QLatin1Char(';'));
                } else {
                    firstElement = false;
                }
                result.append(value.email());
            }
            mLineEdit->setText(result);
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

bool EmailLineEdit::isValid() const
{
    return mEmailIsValid;
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
    mEmailIsValid = lineEditText.contains(QLatin1Char('@'));
    if (mNegativeBackground.isEmpty()) {
        KStatefulBrush bgBrush = KStatefulBrush(KColorScheme::View, KColorScheme::NegativeText);
        mNegativeBackground = QStringLiteral("QLineEdit{ background-color:%1 }").arg(bgBrush.brush(this).color().name());
    }
    if (!mEmailIsValid) {
        styleSheet = mNegativeBackground;
    }
    mLineEdit->setStyleSheet(styleSheet);
#endif
}

#include "emaillineedit.moc"
