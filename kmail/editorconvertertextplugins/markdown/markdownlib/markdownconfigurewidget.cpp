/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

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
    : MessageComposer::PluginEditorConvertTextConfigureWidget(parent)
    , mLatexSupport(new QCheckBox(i18n("Enable embedded LaTeX"), this))
    , mExtraDefinitionLists(new QCheckBox(i18n("Enable PHP Markdown Extra definition lists"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mLatexSupport->setObjectName(QStringLiteral("latex"));
    mainLayout->addWidget(mLatexSupport);

    mExtraDefinitionLists->setObjectName(QStringLiteral("extradefinitionlists"));
    mainLayout->addWidget(mExtraDefinitionLists);
    mainLayout->addStretch(1);
}

MarkdownConfigureWidget::~MarkdownConfigureWidget()
{
}

void MarkdownConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    mLatexSupport->setChecked(grp.readEntry("Enable Embedded Latex", false));
    mExtraDefinitionLists->setChecked(grp.readEntry("Enable Extra Definition Lists", false));
}

void MarkdownConfigureWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
    grp.writeEntry("Enable Embedded Latex", mLatexSupport->isChecked());
    grp.writeEntry("Enable Extra Definition Lists", mExtraDefinitionLists->isChecked());
}

void MarkdownConfigureWidget::resetSettings()
{
    mLatexSupport->setChecked(false);
    mExtraDefinitionLists->setChecked(false);
}
