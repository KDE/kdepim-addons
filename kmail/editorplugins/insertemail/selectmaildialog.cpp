/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmaildialog.h"
using namespace Qt::Literals::StringLiterals;

#include "selectmailwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

namespace
{
const char myConfigGroupName[] = "SelectMailDialog";
}
SelectMailDialog::SelectMailDialog(QWidget *parent)
    : QDialog(parent)
    , mSelectMailWidget(new SelectMailWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Select Email Address"));
    auto mainLayout = new QVBoxLayout(this);

    mSelectMailWidget->setObjectName(QLatin1StringView("selectmailwidget"));
    mainLayout->addWidget(mSelectMailWidget);
    connect(mSelectMailWidget, &SelectMailWidget::doubleClicked, this, &SelectMailDialog::slotInsertEmails);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SelectMailDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SelectMailDialog::reject);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

SelectMailDialog::~SelectMailDialog()
{
    writeConfig();
}

QStringList SelectMailDialog::selectedEmails() const
{
    return mSelectMailWidget->selectedEmails();
}

void SelectMailDialog::slotInsertEmails()
{
    Q_EMIT emailSelected(selectedEmails());
    accept();
}

void SelectMailDialog::accept()
{
    const QStringList emails = selectedEmails();
    if (!emails.isEmpty()) {
        Q_EMIT emailSelected(emails);
    }
    QDialog::accept();
}

void SelectMailDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfigGroupName), 300, 200);
}

void SelectMailDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_selectmaildialog.cpp"
