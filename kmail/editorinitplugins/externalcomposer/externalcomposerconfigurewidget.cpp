/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerconfigurewidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KConfigGroup>
#include <KLineEdit>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KUrlRequester>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
namespace
{
const char myExternalComposerGroupName[] = "External Composer";
}
ExternalComposerConfigureWidget::ExternalComposerConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mExternalEditorCheck(new QCheckBox(i18nc("@option:check", "Use external editor instead of composer"), this))
    , mEditorRequester(new KUrlRequester(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mExternalEditorCheck->setObjectName(QLatin1StringView("enabled"));
    mExternalEditorCheck->setChecked(false);
    mainLayout->addWidget(mExternalEditorCheck);

    auto hbox = new QHBoxLayout;
    auto label = new QLabel(u"Specify editor:"_s, this);
    label->setObjectName(QLatin1StringView("urlrequesterlabel"));
    hbox->addWidget(label);

    mEditorRequester->setObjectName(QLatin1StringView("mEditorRequester"));
    hbox->addWidget(mEditorRequester);

    mEditorRequester->setMimeTypeFilters({u"application/x-executable"_s, u"application/x-shellscript"_s, QStringLiteral("application/x-desktop")});

    mEditorRequester->setMode(KFile::File | KFile::ExistingOnly | KFile::LocalOnly);
    mEditorRequester->setEnabled(false);
    KLineEditEventHandler::catchReturnKey(mEditorRequester->lineEdit());

    mainLayout->addLayout(hbox);

    label = new QLabel(i18nc("@label:textbox",
                             "<b>%f</b> will be replaced with the "
                             "filename to edit.<br />"
                             "<b>%w</b> will be replaced with the window id.<br />"
                             "<b>%l</b> will be replaced with the line number."),
                       this);
    label->setObjectName(QLatin1StringView("explanationlabel"));
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
    KConfigGroup group = config->group(QLatin1StringView(myExternalComposerGroupName));
    mExternalEditorCheck->setChecked(group.readEntry("Enabled", false));
    mEditorRequester->setText(group.readEntry("ComposerPath", u"kwrite %f"_s));
}

void ExternalComposerConfigureWidget::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(QLatin1StringView(myExternalComposerGroupName));
    group.writeEntry("Enabled", mExternalEditorCheck->isChecked());
    group.writeEntry("ComposerPath", mEditorRequester->text());
}

void ExternalComposerConfigureWidget::resetSettings()
{
    mExternalEditorCheck->setChecked(false);
    mEditorRequester->setText(u"kwrite %f"_s);
}

#include "moc_externalcomposerconfigurewidget.cpp"
