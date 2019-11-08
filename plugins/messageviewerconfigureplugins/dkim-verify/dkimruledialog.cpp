/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimruledialog.h"
#include "dkimrulewidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace {
static const char myConfigGroupName[] = "DKIMRuleDialog";
}

DKIMRuleDialog::DKIMRuleDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Add Rule"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mRuleWidget = new DKIMRuleWidget(this);
    mRuleWidget->setObjectName(QStringLiteral("rulewidget"));
    mainLayout->addWidget(mRuleWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    QPushButton *importButton = new QPushButton(i18n("Import..."), this);
    buttonBox->addButton(importButton, QDialogButtonBox::ActionRole);
    connect(importButton, &QPushButton::clicked, this, &DKIMRuleDialog::slotImport);
    QPushButton *exportButton = new QPushButton(i18n("Export..."), this);
    buttonBox->addButton(exportButton, QDialogButtonBox::ActionRole);
    connect(exportButton, &QPushButton::clicked, this, &DKIMRuleDialog::slotExport);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DKIMRuleDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DKIMRuleDialog::reject);
    readConfig();
}

DKIMRuleDialog::~DKIMRuleDialog()
{
    writeConfig();
}

void DKIMRuleDialog::slotAccepted()
{
    accept();
}

void DKIMRuleDialog::slotExport()
{

}

void DKIMRuleDialog::slotImport()
{

}

void DKIMRuleDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void DKIMRuleDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    group.writeEntry("Size", size());
    group.sync();
}

void DKIMRuleDialog::loadRule(const MessageViewer::DKIMRule &rule)
{
    setWindowTitle(i18n("Modify Rule"));
    mRuleWidget->loadRule(rule);
}

MessageViewer::DKIMRule DKIMRuleDialog::rule() const
{
    return mRuleWidget->rule();
}
