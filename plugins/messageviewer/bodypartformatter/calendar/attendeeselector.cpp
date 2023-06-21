/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "attendeeselector.h"

#include <KEmailAddress>
#include <PimCommonAkonadi/AddresseeLineEdit>

#include <KGuiItem>
#include <KLocalizedString>
#include <KStandardGuiItem>
#include <QDialogButtonBox>
#include <QVBoxLayout>

AttendeeSelector::AttendeeSelector(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Select Attendees"));
    auto mainLayout = new QVBoxLayout(this);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    auto mainWidget = new QWidget(this);
    mainLayout->addWidget(mainWidget);
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    mOkButton->setDefault(true);
    mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AttendeeSelector::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AttendeeSelector::reject);
    mainLayout->addWidget(buttonBox);

    ui.setupUi(mainWidget);

    KGuiItem::assign(ui.addButton, KStandardGuiItem::add());
    connect(ui.addButton, &QPushButton::clicked, this, &AttendeeSelector::addClicked);
    KGuiItem::assign(ui.removeButton, KStandardGuiItem::remove());
    connect(ui.removeButton, &QPushButton::clicked, this, &AttendeeSelector::removeClicked);

    ui.attendeeEdit->setPlaceholderText(i18n("Click to add a new attendee"));
    connect(ui.attendeeEdit, &PimCommon::AddresseeLineEdit::textChanged, this, &AttendeeSelector::textChanged);
    connect(ui.attendeeEdit, &PimCommon::AddresseeLineEdit::returnPressed, this, &AttendeeSelector::addClicked);

    connect(ui.attendeeList, &QListWidget::itemSelectionChanged, this, &AttendeeSelector::selectionChanged);
    mOkButton->setEnabled(false);
}

QStringList AttendeeSelector::attendees() const
{
    QStringList rv;
    const int numberOfAttendee(ui.attendeeList->count());
    rv.reserve(numberOfAttendee);
    for (int i = 0; i < numberOfAttendee; ++i) {
        const QString addr = ui.attendeeList->item(i)->text();

        // Build a nice address for this attendee including the CN.
        QString tname;
        QString temail;
        KEmailAddress::extractEmailAddressAndName(addr, temail, tname); // ignore return value
        // which is always false
        rv << temail;
    }
    return rv;
}

void AttendeeSelector::addClicked()
{
    const QString str = ui.attendeeEdit->text();
    if (!str.isEmpty()) {
        ui.attendeeList->addItem(str);
    }
    ui.attendeeEdit->clear();
    mOkButton->setEnabled(true);
}

void AttendeeSelector::removeClicked()
{
    delete ui.attendeeList->takeItem(ui.attendeeList->currentRow());
    mOkButton->setEnabled((ui.attendeeList->count() > 0));
}

void AttendeeSelector::textChanged(const QString &text)
{
    ui.addButton->setEnabled(!text.isEmpty());
}

void AttendeeSelector::selectionChanged()
{
    ui.removeButton->setEnabled(ui.attendeeList->currentItem());
}

#include "moc_attendeeselector.cpp"
