/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatedialog.h"
#include "gravatarupdatewidget.h"
#include <QVBoxLayout>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace KABGravatar;

GravatarUpdateDialog::GravatarUpdateDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("@title:window", "Check and update Gravatar"));
    mGravatarUpdateWidget = new GravatarUpdateWidget(this);
    connect(mGravatarUpdateWidget, &GravatarUpdateWidget::activateDialogButton, this, &GravatarUpdateDialog::slotActivateButton);
    mGravatarUpdateWidget->setObjectName(QStringLiteral("gravatarupdatewidget"));
    mainLayout->addWidget(mGravatarUpdateWidget);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    mSaveImageButton = new QPushButton(i18n("Save Image"), this);
    mSaveImageButton->setEnabled(false);
    buttonBox->addButton(mSaveImageButton, QDialogButtonBox::ActionRole);
    connect(mSaveImageButton, &QPushButton::clicked, this, &GravatarUpdateDialog::slotSaveImage);

    mSaveUrlButton = new QPushButton(i18n("Save Image URL"), this);
    buttonBox->addButton(mSaveUrlButton, QDialogButtonBox::ActionRole);
    mSaveUrlButton->setEnabled(false);
    connect(mSaveUrlButton, &QPushButton::clicked, this, &GravatarUpdateDialog::slotSaveUrl);

    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

GravatarUpdateDialog::~GravatarUpdateDialog()
{
    writeConfig();
}

void GravatarUpdateDialog::slotActivateButton(bool state)
{
    mSaveUrlButton->setEnabled(state);
    mSaveImageButton->setEnabled(state);
}

bool GravatarUpdateDialog::saveUrl() const
{
    return mSaveUrl;
}

void GravatarUpdateDialog::slotSaveUrl()
{
    mSaveUrl = true;
    accept();
}

void GravatarUpdateDialog::slotSaveImage()
{
    mSaveUrl = false;
    accept();
}

void GravatarUpdateDialog::setEmail(const QString &email)
{
    mGravatarUpdateWidget->setEmail(email);
}

QPixmap GravatarUpdateDialog::pixmap() const
{
    return mGravatarUpdateWidget->pixmap();
}

void GravatarUpdateDialog::setOriginalUrl(const QUrl &url)
{
    mGravatarUpdateWidget->setOriginalUrl(url);
}

QUrl GravatarUpdateDialog::resolvedUrl() const
{
    return mGravatarUpdateWidget->resolvedUrl();
}

void GravatarUpdateDialog::setOriginalPixmap(const QPixmap &pix)
{
    mGravatarUpdateWidget->setOriginalPixmap(pix);
}

void GravatarUpdateDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "GravatarUpdateDialog");
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void GravatarUpdateDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "GravatarUpdateDialog");
    grp.writeEntry("Size", size());
    grp.sync();
}
