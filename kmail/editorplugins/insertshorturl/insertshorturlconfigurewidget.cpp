/*
   Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

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

#include "insertshorturlconfigurewidget.h"
#include "shorturlengineplugin/shorturlengineplugin.h"
#include "shorturlengineplugin/shorturlenginepluginmanager.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

InsertShorturlConfigureWidget::InsertShorturlConfigureWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *lab = new QLabel(i18n("Select Short URL server:"), this);
    lab->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(lab);

    mShortUrlServer = new QComboBox(this);
    mShortUrlServer->setObjectName(QStringLiteral("shorturlserver"));
    mainLayout->addWidget(mShortUrlServer);
    const QVector<ShortUrlEnginePlugin *> lstPlugin = ShortUrlEnginePluginManager::self()->pluginsList();
    for (ShortUrlEnginePlugin *plugin : lstPlugin) {
        mShortUrlServer->addItem(plugin->pluginName(), plugin->engineName());
    }

    connect(mShortUrlServer, QOverload<int>::of(&QComboBox::activated), this, &InsertShorturlConfigureWidget::slotChanged);
    loadConfig();
}

InsertShorturlConfigureWidget::~InsertShorturlConfigureWidget()
{
}

void InsertShorturlConfigureWidget::slotChanged()
{
    mChanged = true;
}

void InsertShorturlConfigureWidget::loadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "ShortUrl");
    const QString engineName = grp.readEntry("EngineName");
    int index = mShortUrlServer->findData(engineName);
    if (index < 0) {
        index = 0;
    }
    mShortUrlServer->setCurrentIndex(index);
    mChanged = false;
}

void InsertShorturlConfigureWidget::writeConfig()
{
    if (mChanged) {
        KConfigGroup grp(KSharedConfig::openConfig(), "ShortUrl");
        grp.writeEntry("EngineName", mShortUrlServer->itemData(mShortUrlServer->currentIndex()).toString());
        grp.sync();
    }
}
