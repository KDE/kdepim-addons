/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "externalcomposerconfigurewidget.h"
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QVBoxLayout>
#include <QCheckBox>
#include <KUrlRequester>
#include <QLabel>

ExternalComposerConfigureWidget::ExternalComposerConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorInitConfigureWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mExternalEditorCheck = new QCheckBox(i18n("Use external editor instead of composer"), this);
    mExternalEditorCheck->setObjectName(QStringLiteral("enabled"));
    mExternalEditorCheck->setChecked(false);
    mainLayout->addWidget(mExternalEditorCheck);

    QHBoxLayout *hbox = new QHBoxLayout;
    QLabel *label = new QLabel(QStringLiteral("Specify editor:"), this);
    label->setObjectName(QStringLiteral("urlrequesterlabel"));
    hbox->addWidget(label);

    mEditorRequester = new KUrlRequester(this);
    mEditorRequester->setObjectName(QStringLiteral("mEditorRequester"));
    hbox->addWidget(mEditorRequester);

    mEditorRequester->setMimeTypeFilters({QStringLiteral("application/x-executable"),
                                          QStringLiteral("application/x-shellscript"),
                                          QStringLiteral("application/x-desktop")});

    mEditorRequester->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mEditorRequester->setEnabled(false);

    mainLayout->addLayout(hbox);

    label = new QLabel(i18n("<b>%f</b> will be replaced with the "
                            "filename to edit.<br />"
                            "<b>%w</b> will be replaced with the window id.<br />"
                            "<b>%l</b> will be replaced with the line number."), this);
    label->setObjectName(QStringLiteral("explanationlabel"));
    label->setEnabled(false);   // see above
    mainLayout->addWidget(label);

    mainLayout->addStretch(1);

    connect(mExternalEditorCheck, &QAbstractButton::toggled,
            label, &QWidget::setEnabled);
    connect(mExternalEditorCheck, &QAbstractButton::toggled,
            mEditorRequester, &QWidget::setEnabled);
}

ExternalComposerConfigureWidget::~ExternalComposerConfigureWidget()
{
}

void ExternalComposerConfigureWidget::loadSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(QStringLiteral("External Composer"));
    mExternalEditorCheck->setChecked(group.readEntry("Enabled", false));
    mEditorRequester->setText(group.readEntry("ComposerPath", QStringLiteral("kwrite %f")));
}

void ExternalComposerConfigureWidget::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(QStringLiteral("External Composer"));
    group.writeEntry("Enabled", mExternalEditorCheck->isChecked());
    group.writeEntry("ComposerPath", mEditorRequester->text());
}

void ExternalComposerConfigureWidget::resetSettings()
{
    mExternalEditorCheck->setChecked(false);
    mEditorRequester->setText(QStringLiteral("kwrite %f"));
}
