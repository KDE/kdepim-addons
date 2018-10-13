/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#include "markdownconfigurewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QCheckBox>

MarkdownConfigureWidget::MarkdownConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConvertTextConfigureWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    mLatexSupport = new QCheckBox(i18n("Enable embedded LaTeX"), this);
    mLatexSupport->setObjectName(QStringLiteral("latex"));
    mainLayout->addWidget(mLatexSupport);

    mExtraDefinitionLists = new QCheckBox(i18n("Enable PHP Markdown Extra definition lists"), this);
    mExtraDefinitionLists->setObjectName(QStringLiteral("extradefinitionlists"));
    mainLayout->addWidget(mExtraDefinitionLists);
}

MarkdownConfigureWidget::~MarkdownConfigureWidget()
{
}

void MarkdownConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Mardown");
    mLatexSupport->setChecked(grp.readEntry("Enable Embedded Latex", false));
    mExtraDefinitionLists->setChecked(grp.readEntry("Enable Extra Definition Lists", false));
}

void MarkdownConfigureWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Mardown");
    grp.writeEntry("Enable Embedded Latex", mLatexSupport->isChecked());
    grp.writeEntry("Enable Extra Definition Lists", mExtraDefinitionLists->isChecked());
}

void MarkdownConfigureWidget::resetSettings()
{
    mLatexSupport->setChecked(false);
    mExtraDefinitionLists->setChecked(false);
}
