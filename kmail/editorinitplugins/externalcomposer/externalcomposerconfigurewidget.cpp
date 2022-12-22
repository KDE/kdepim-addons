/*
   SPDX-FileCopyrightText: 2017-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KUrlRequester>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
namespace
{
static const char myExternalComposerGroupName[] = "External Composer";
}
ExternalComposerConfigureWidget::ExternalComposerConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mExternalEditorCheck(new QCheckBox(i18n("Use external editor instead of composer"), this))
    , mEditorRequester(new KUrlRequester(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mExternalEditorCheck->setObjectName(QStringLiteral("enabled"));
    mExternalEditorCheck->setChecked(false);
    mainLayout->addWidget(mExternalEditorCheck);

    auto hbox = new QHBoxLayout;
    auto label = new QLabel(QStringLiteral("Specify editor:"), this);
    label->setObjectName(QStringLiteral("urlrequesterlabel"));
    hbox->addWidget(label);

    mEditorRequester->setObjectName(QStringLiteral("mEditorRequester"));
    hbox->addWidget(mEditorRequester);

    mEditorRequester->setMimeTypeFilters(
        {QStringLiteral("application/x-executable"), QStringLiteral("application/x-shellscript"), QStringLiteral("application/x-desktop")});

    mEditorRequester->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mEditorRequester->setEnabled(false);

    mainLayout->addLayout(hbox);

    label = new QLabel(i18n("<b>%f</b> will be replaced with the "
                            "filename to edit.<br />"
                            "<b>%w</b> will be replaced with the window id.<br />"
                            "<b>%l</b> will be replaced with the line number."),
                       this);
    label->setObjectName(QStringLiteral("explanationlabel"));
    label->setEnabled(false); // see above
    mainLayout->addWidget(label);

    mainLayout->addStretch(1);

    connect(mExternalEditorCheck, &QAbstractButton::toggled, label, &QWidget::setEnabled);
    connect(mExternalEditorCheck, &QAbstractButton::toggled, mEditorRequester, &QWidget::setEnabled);
}

ExternalComposerConfigureWidget::~ExternalComposerConfigureWidget() = default;

void ExternalComposerConfigureWidget::loadSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(myExternalComposerGroupName);
    mExternalEditorCheck->setChecked(group.readEntry("Enabled", false));
    mEditorRequester->setText(group.readEntry("ComposerPath", QStringLiteral("kwrite %f")));
}

void ExternalComposerConfigureWidget::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(myExternalComposerGroupName);
    group.writeEntry("Enabled", mExternalEditorCheck->isChecked());
    group.writeEntry("ComposerPath", mEditorRequester->text());
}

void ExternalComposerConfigureWidget::resetSettings()
{
    mExternalEditorCheck->setChecked(false);
    mEditorRequester->setText(QStringLiteral("kwrite %f"));
}
