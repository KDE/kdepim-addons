/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QCheckBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
namespace
{
const char myConfigGroupName[] = "Markdown";
}
MarkdownConfigureWidget::MarkdownConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConfigureBaseWidget(parent)
    , mLatexSupport(new QCheckBox(i18nc("@option:check", "Enable embedded LaTeX"), this))
    , mExtraDefinitionLists(new QCheckBox(i18nc("@option:check", "Enable PHP Markdown Extra definition lists"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);
    mainLayout->setContentsMargins({});

    mLatexSupport->setObjectName("latex"_L1);
    mainLayout->addWidget(mLatexSupport);

    mExtraDefinitionLists->setObjectName("extradefinitionlists"_L1);
    mainLayout->addWidget(mExtraDefinitionLists);
    mainLayout->addStretch(1);
}

MarkdownConfigureWidget::~MarkdownConfigureWidget() = default;

void MarkdownConfigureWidget::loadSettings()
{
    const KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
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
