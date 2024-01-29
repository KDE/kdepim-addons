/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatedialog.h"
#include "gravatarupdatewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

using namespace KABGravatar;
namespace
{
static const char myConfigGroupName[] = "GravatarUpdateDialog";
}
GravatarUpdateDialog::GravatarUpdateDialog(QWidget *parent)
    : QDialog(parent)
    , mGravatarUpdateWidget(new GravatarUpdateWidget(this))
    , mSaveImageButton(new QPushButton(i18n("Save Image"), this))
    , mSaveUrlButton(new QPushButton(i18n("Save Image URL"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    setWindowTitle(i18nc("@title:window", "Check and update Gravatar"));
    connect(mGravatarUpdateWidget, &GravatarUpdateWidget::activateDialogButton, this, &GravatarUpdateDialog::slotActivateButton);
    mGravatarUpdateWidget->setObjectName(QLatin1StringView("gravatarupdatewidget"));
    mainLayout->addWidget(mGravatarUpdateWidget);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
    mSaveImageButton->setEnabled(false);
    buttonBox->addButton(mSaveImageButton, QDialogButtonBox::ActionRole);
    connect(mSaveImageButton, &QPushButton::clicked, this, &GravatarUpdateDialog::slotSaveImage);

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
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void GravatarUpdateDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), grp);
    grp.sync();
}

#include "moc_gravatarupdatedialog.cpp"
