/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QCheckBox>
#include <QVBoxLayout>
namespace
{
static const char myConfigGroupName[] = "Markdown";
}
MarkdownConfigureWidget::MarkdownConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mLatexSupport(new QCheckBox(i18nc("@option:check", "Enable embedded LaTeX"), this))
    , mExtraDefinitionLists(new QCheckBox(i18nc("@option:check", "Enable PHP Markdown Extra definition lists"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    mLatexSupport->setObjectName(QLatin1StringView("latex"));
    mainLayout->addWidget(mLatexSupport);

    mExtraDefinitionLists->setObjectName(QLatin1StringView("extradefinitionlists"));
    mainLayout->addWidget(mExtraDefinitionLists);
    mainLayout->addStretch(1);
}

MarkdownConfigureWidget::~MarkdownConfigureWidget() = default;

void MarkdownConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
    mLatexSupport->setChecked(grp.readEntry("Enable Embedded Latex", false));
    mExtraDefinitionLists->setChecked(grp.readEntry("Enable Extra Definition Lists", false));
}

void MarkdownConfigureWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
    grp.writeEntry("Enable Embedded Latex", mLatexSupport->isChecked());
    grp.writeEntry("Enable Extra Definition Lists", mExtraDefinitionLists->isChecked());
}

void MarkdownConfigureWidget::resetSettings()
{
    mLatexSupport->setChecked(false);
    mExtraDefinitionLists->setChecked(false);
}

#include "moc_markdownconfigurewidget.cpp"
