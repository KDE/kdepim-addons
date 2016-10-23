/*
   Copyright (C) 2013-2016 Montel Laurent <montel@kde.org>

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

#include "shorturlconfigurewidget.h"
#include "shorturlengineplugin/shorturlenginepluginmanager.h"

#include <KLocalizedString>

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <KConfigGroup>
#include <KSharedConfig>

#include "shorturlengineplugin/shorturlengineplugin.h"

class ShortUrlConfigureWidgetPrivate
{
public:
    ShortUrlConfigureWidgetPrivate()
        : mShortUrlServer(Q_NULLPTR),
          mChanged(false)
    {

    }
    QComboBox *mShortUrlServer;
    bool mChanged;
};

ShortUrlConfigureWidget::ShortUrlConfigureWidget(QWidget *parent)
    : QWidget(parent),
      d(new ShortUrlConfigureWidgetPrivate)
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setMargin(0);

    QLabel *lab = new QLabel(i18n("Select Short URL server:"), this);
    lay->addWidget(lab);

    d->mShortUrlServer = new QComboBox(this);
    connect(d->mShortUrlServer, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &ShortUrlConfigureWidget::slotChanged);
    lay->addWidget(d->mShortUrlServer);
    init();
    loadConfig();
}

ShortUrlConfigureWidget::~ShortUrlConfigureWidget()
{
    delete d;
}

void ShortUrlConfigureWidget::slotChanged()
{
    d->mChanged = true;
}

void ShortUrlConfigureWidget::init()
{
    const QVector<ShortUrlEnginePlugin *>  lstPlugin = ShortUrlEnginePluginManager::self()->pluginsList();
    Q_FOREACH (ShortUrlEnginePlugin *plugin, lstPlugin) {
        d->mShortUrlServer->addItem(plugin->pluginName(), plugin->engineName());
    }
}

void ShortUrlConfigureWidget::loadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "ShortUrl");
    const QString engineName = grp.readEntry("EngineName");
    int index = d->mShortUrlServer->findData(engineName);
    if (index < 0) {
        index = 0;
    }
    d->mShortUrlServer->setCurrentIndex(index);
    d->mChanged = false;
}

void ShortUrlConfigureWidget::writeConfig()
{
    if (d->mChanged) {
        KConfigGroup grp(KSharedConfig::openConfig(), "ShortUrl");
        const QString engineName = grp.readEntry("EngineName");
        grp.writeEntry("EngineName", d->mShortUrlServer->itemData(d->mShortUrlServer->currentIndex()).toString());
        grp.sync();
        Q_EMIT settingsChanged();
    }
    d->mChanged = false;
}

void ShortUrlConfigureWidget::resetToDefault()
{
    d->mShortUrlServer->setCurrentIndex(0);
    d->mChanged = false;
}

