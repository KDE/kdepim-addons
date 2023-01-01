/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>
    SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "delegateselector.h"

#include <PimCommonAkonadi/AddresseeLineEdit>

#include <KLocalizedString>

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

DelegateSelector::DelegateSelector(QWidget *parent)
    : QDialog(parent)
    , mDelegate(new PimCommon::AddresseeLineEdit(this))
    , mRsvp(new QCheckBox(i18n("Keep me informed about status changes of this incidence."), this))
{
    setWindowTitle(i18nc("@title:window", "Select delegate"));
    auto mainLayout = new QVBoxLayout(this);

    auto label = new QLabel(i18n("Delegate:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mDelegate->setObjectName(QStringLiteral("delegate"));
    mainLayout->addWidget(mDelegate);

    connect(mDelegate, &PimCommon::AddresseeLineEdit::textChanged, this, &DelegateSelector::slotTextChanged);
    mRsvp->setObjectName(QStringLiteral("informcheckbox"));

    mRsvp->setChecked(true);
    mainLayout->addWidget(mRsvp);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    mOkButton->setObjectName(QStringLiteral("okbutton"));
    mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &DelegateSelector::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DelegateSelector::reject);
    mOkButton->setDefault(true);
    mOkButton->setEnabled(false);

    mainLayout->addWidget(buttonBox);
}

void DelegateSelector::slotTextChanged(const QString &text)
{
    mOkButton->setEnabled(!text.trimmed().isEmpty());
}

QString DelegateSelector::delegate() const
{
    return mDelegate->text();
}

bool DelegateSelector::rsvp() const
{
    return mRsvp->isChecked();
}
