/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emaillineedit.h"
#include "sieveeditoremaillineditplugin_debug.h"
#include <Akonadi/EmailAddressSelectionDialog>
#include <KPluginFactory>
#include <KStatefulBrush>

#include <KColorScheme>
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QTreeView>
#include <memory>

K_PLUGIN_CLASS_WITH_JSON(EmailLineEdit, "emaillineedit.json")

EmailLineEdit::EmailLineEdit(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractSelectEmailLineEdit(parent)
    , mLineEdit(new QLineEdit(this))
    , mEmailButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mLineEdit->setClearButtonEnabled(true);
    mLineEdit->setPlaceholderText(i18n("Click on button for selecting contacts..."));
    connect(mLineEdit, &QLineEdit::textChanged, this, &EmailLineEdit::slotTextChanged);
    mainLayout->addWidget(mLineEdit);

    mEmailButton->setText(i18n("..."));
    mEmailButton->setObjectName(QStringLiteral("emailbutton"));
    mEmailButton->setToolTip(i18n("Select Emails"));
    mainLayout->addWidget(mEmailButton);
    connect(mEmailButton, &QToolButton::clicked, this, &EmailLineEdit::slotSelectEmail);
    verifyAkonadiStatus();
    connect(Akonadi::ServerManager::self(), &Akonadi::ServerManager::stateChanged, this, &EmailLineEdit::akonadiStateChanged);
    verifyAddress();
}

EmailLineEdit::~EmailLineEdit() = default;

void EmailLineEdit::akonadiStateChanged(Akonadi::ServerManager::State state)
{
    mEmailButton->setVisible(state == Akonadi::ServerManager::Running);
}

void EmailLineEdit::verifyAkonadiStatus()
{
    const Akonadi::ServerManager::State state = Akonadi::ServerManager::self()->state();
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
    const KPluginMetaData editWidgetPlugin(QStringLiteral("pim6/akonadi/emailaddressselectionldapdialogplugin"));

    const auto result = KPluginFactory::instantiatePlugin<Akonadi::AbstractEmailAddressSelectionDialog>(editWidgetPlugin);
    if (result) {
        dlg.reset(result.plugin);
    } else {
        dlg = std::make_unique<Akonadi::EmailAddressSelectionDialog>(this);
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
        mNegativeBackground = QStringLiteral("QLineEdit{ background-color:%1 }").arg(bgBrush.brush(palette()).color().name());
    }
    if (!mEmailIsValid) {
        styleSheet = mNegativeBackground;
    }
    mLineEdit->setStyleSheet(styleSheet);
#endif
}

#include "emaillineedit.moc"
