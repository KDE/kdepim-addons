/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "selectattachmentdialog.h"
#include <KLocalizedString>
#include <KUrlRequester>
#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>
using namespace MailMerge;

SelectAttachmentDialog::SelectAttachmentDialog(QWidget *parent)
    : QDialog(parent)
    , mUrlRequester(new KUrlRequester(this))
{
    setWindowTitle(i18nc("@title:window", "Attachment"));
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    auto mainLayout = new QVBoxLayout(this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto w = new QWidget;
    auto vbox = new QVBoxLayout(w);
    vbox->setContentsMargins({});
    auto lab = new QLabel(i18n("Select attachment:"), this);
    lab->setObjectName(QStringLiteral("selectattachment_label"));
    vbox->addWidget(lab);
    mUrlRequester->setMode(KFile::LocalOnly | KFile::ExistingOnly);
    mUrlRequester->setObjectName(QStringLiteral("urlrequester"));
    vbox->addWidget(mUrlRequester);
    mainLayout->addWidget(w);
    mainLayout->addWidget(buttonBox);
}

SelectAttachmentDialog::~SelectAttachmentDialog() = default;

void SelectAttachmentDialog::setAttachmentPath(const QUrl &path)
{
    mUrlRequester->setUrl(path);
}

QString SelectAttachmentDialog::attachmentPath() const
{
    return mUrlRequester->url().path();
}
