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
#include <QComboBox>
#include <QLabel>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>

MarkdownConfigureWidget::MarkdownConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorConvertTextConfigureWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    QLabel *lab = new QLabel(i18n("Select CSS"), this);
    lab->setObjectName(QStringLiteral("labelcss"));
    mainLayout->addWidget(lab);

    mCssCombobox = new QComboBox(this);
    mCssCombobox->setObjectName(QStringLiteral("csscombobox"));
    mainLayout->addWidget(mCssCombobox);
    fillCombobox();
}

MarkdownConfigureWidget::~MarkdownConfigureWidget()
{

}

void MarkdownConfigureWidget::fillCombobox()
{

}

void MarkdownConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Mardown");
    const QString cssname = grp.readEntry(QStringLiteral("cssname"), QString());
    if (!cssname.isEmpty()) {
        const int index = mCssCombobox->findText(cssname);
        if (index > -1) {
            mCssCombobox->setCurrentIndex(index);
        }
    }
}

void MarkdownConfigureWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Mardown");
    grp.writeEntry(QStringLiteral("cssname"), mCssCombobox->currentText());
}

void MarkdownConfigureWidget::resetSettings()
{
    mCssCombobox->setCurrentIndex(0);
}
