/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "selectattachmentdialog.h"
#include <KLocalizedString>
#include <kurlrequester.h>
#include <QLabel>
#include <QDialogButtonBox>
using namespace MailMerge;

SelectAttachmentDialog::SelectAttachmentDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Attachment"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QWidget *w = new QWidget;
    QVBoxLayout *vbox = new QVBoxLayout;
    w->setLayout(vbox);
    QLabel *lab = new QLabel(i18n("Select attachment:"));
    lab->setObjectName(QStringLiteral("selectattachment_label"));
    vbox->addWidget(lab);
    mUrlRequester = new KUrlRequester;
    mUrlRequester->setMode(KFile::LocalOnly | KFile::ExistingOnly);
    mUrlRequester->setObjectName(QStringLiteral("urlrequester"));
    vbox->addWidget(mUrlRequester);
    mainLayout->addWidget(w);
    mainLayout->addWidget(buttonBox);
}

SelectAttachmentDialog::~SelectAttachmentDialog()
{
}

void SelectAttachmentDialog::setAttachmentPath(const QString &path)
{
    mUrlRequester->setUrl(path);
}

QString SelectAttachmentDialog::attachmentPath() const
{
    return mUrlRequester->url().path();
}
