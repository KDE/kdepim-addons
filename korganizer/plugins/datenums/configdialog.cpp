/*
  This file is part of KOrganizer.

  SPDX-FileCopyrightText: 2001 Cornelius Schumacher <schumacher@kde.org>
  SPDX-FileCopyrightText: 2003-2004 Reinhold Kainhofer <reinhold@kainhofer.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "configdialog.h"
#include "datenums.h"

#include <KConfig>
#include <KLocalizedString>

#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QPushButton>

ConfigDialog::ConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Day Numbers"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfigDialog::reject);
    okButton->setDefault(true);
    setModal(true);
    QFrame *topFrame = new QFrame(this);
    mainLayout->addWidget(topFrame);
    mainLayout->addStretch(1);
    mainLayout->addWidget(buttonBox);
    QVBoxLayout *topLayout = new QVBoxLayout(topFrame);
    topLayout->setContentsMargins({});

    QGroupBox *dayNumBox = new QGroupBox(i18n("Show Date Number"), topFrame);
    topLayout->addWidget(dayNumBox);
    QVBoxLayout *groupLayout = new QVBoxLayout(dayNumBox);

    mDayNumGroup = new QButtonGroup(this);
    QRadioButton *btn = new QRadioButton(i18n("Show day number"), dayNumBox);
    mDayNumGroup->addButton(btn, int(Datenums::DayOfYear));
    groupLayout->addWidget(btn);
    btn = new QRadioButton(i18n("Show days to end of year"), dayNumBox);
    mDayNumGroup->addButton(btn, int(Datenums::DaysRemaining));
    groupLayout->addWidget(btn);
    btn = new QRadioButton(i18n("Show both"), dayNumBox);
    mDayNumGroup->addButton(btn, int(Datenums::DayOfYear | Datenums::DaysRemaining));
    groupLayout->addWidget(btn);

    connect(okButton, &QPushButton::clicked, this, &ConfigDialog::slotOk);

    load();
}

ConfigDialog::~ConfigDialog()
{
}

void ConfigDialog::load()
{
    KConfig _config(QStringLiteral("korganizerrc"), KConfig::NoGlobals);
    KConfigGroup config(&_config, "Calendar/Datenums Plugin");
    int datenum = config.readEntry(
        "ShowDayNumbers", int(Datenums::DayOfYear | Datenums::DaysRemaining));
    QAbstractButton *btn = mDayNumGroup->button(datenum);
    if (!btn) {
        btn = mDayNumGroup->button(int(Datenums::DayOfYear | Datenums::DaysRemaining));
    }
    btn->setChecked(true);
}

void ConfigDialog::save()
{
    KConfig _config(QStringLiteral("korganizerrc"), KConfig::NoGlobals);
    KConfigGroup config(&_config, "Calendar/Datenums Plugin");
    config.writeEntry("ShowDayNumbers", mDayNumGroup->checkedId());
    config.sync();
}

void ConfigDialog::slotOk()
{
    save();
    accept();
}
