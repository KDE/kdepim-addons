/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "vcardviewerdialog.h"
#include <Akonadi/GrantleeContactViewer>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KStandardGuiItem>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myConfigVCardViewerDialog[] = "VCardViewerDialog";
}
VCardViewerDialog::VCardViewerDialog(const KContacts::Addressee::List &list, QWidget *parent)
    : QDialog(parent)
    , mContacts(list)
{
    setWindowTitle(i18nc("@title:window", "Import vCard"));
    auto mainLayout = new QVBoxLayout(this);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Apply, this);

    auto user1Button = new QPushButton(this);
    buttonBox->addButton(user1Button, QDialogButtonBox::ActionRole);
    auto user2Button = new QPushButton(this);
    buttonBox->addButton(user2Button, QDialogButtonBox::ActionRole);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &VCardViewerDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &VCardViewerDialog::reject);
    KGuiItem::assign(user1Button, KStandardGuiItem::cancel());
    KGuiItem::assign(user2Button, KStandardGuiItem::ok());
    mApplyButton = buttonBox->button(QDialogButtonBox::Apply);
    user1Button->setDefault(true);
    setModal(true);

    auto page = new QFrame(this);
    mainLayout->addWidget(page);
    mainLayout->addWidget(buttonBox);

    auto layout = new QVBoxLayout(page);

    auto label = new QLabel(i18nc("@info", "Do you want to import this contact into your address book?"), page);
    QFont font = label->font();
    font.setBold(true);
    label->setFont(font);
    layout->addWidget(label);

    mView = new KAddressBookGrantlee::GrantleeContactViewer(page);

    layout->addWidget(mView);

    buttonBox->button(QDialogButtonBox::Apply)->setText(i18nc("@action:button", "Import All..."));

    mIt = mContacts.begin();

    connect(user2Button, &QPushButton::clicked, this, &VCardViewerDialog::slotYes);
    connect(user1Button, &QPushButton::clicked, this, &VCardViewerDialog::slotNo);
    connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &VCardViewerDialog::slotApply);
    connect(buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &VCardViewerDialog::slotCancel);

    updateView();
    readConfig();
}

VCardViewerDialog::~VCardViewerDialog()
{
    writeConfig();
}

void VCardViewerDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfigVCardViewerDialog));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void VCardViewerDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfigVCardViewerDialog));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

KContacts::Addressee::List VCardViewerDialog::contacts() const
{
    return mContacts;
}

void VCardViewerDialog::updateView()
{
    mView->setRawContact(*mIt);

    KContacts::Addressee::List::Iterator it = mIt;
    mApplyButton->setEnabled(++it != mContacts.end());
}

void VCardViewerDialog::slotYes()
{
    mIt++;

    if (mIt == mContacts.end()) {
        slotApply();
        return;
    }

    updateView();
}

void VCardViewerDialog::slotNo()
{
    if (mIt == mContacts.end()) {
        accept();
        return;
    }
    // remove the current contact from the result set
    mIt = mContacts.erase(mIt);
    if (mIt == mContacts.end()) {
        return;
    }

    updateView();
}

void VCardViewerDialog::slotApply()
{
    QDialog::accept();
}

void VCardViewerDialog::slotCancel()
{
    mContacts.clear();
    reject();
}

#include "moc_vcardviewerdialog.cpp"
