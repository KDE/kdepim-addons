/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectmaildialog.h"
#include "selectmailwidget.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myConfigGroupName[] = "SelectMailDialog";
}
SelectMailDialog::SelectMailDialog(QWidget *parent)
    : QDialog(parent)
    , mSelectMailWidget(new SelectMailWidget(this))
{
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
}

void SelectMailDialog::accept()
{
    Q_EMIT emailSelected(selectedEmails());
    QDialog::accept();
}

void SelectMailDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void SelectMailDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_selectmaildialog.cpp"
