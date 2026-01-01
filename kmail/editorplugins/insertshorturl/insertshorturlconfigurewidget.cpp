/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
namespace
{
const char myConfigGroupName[] = "ShortUrl";
}
InsertShorturlConfigureWidget::InsertShorturlConfigureWidget(QWidget *parent)
    : QWidget(parent)
    , mShortUrlServer(new QComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mainLayout->setContentsMargins({});

    auto lab = new QLabel(i18nc("@label:textbox", "Select Short URL server:"), this);
    lab->setObjectName(QLatin1StringView("label"));
    mainLayout->addWidget(lab);

    mShortUrlServer->setObjectName(QLatin1StringView("shorturlserver"));
    mainLayout->addWidget(mShortUrlServer);
    const QList<ShortUrlEnginePlugin *> lstPlugin = ShortUrlEnginePluginManager::self()->pluginsList();
    for (const ShortUrlEnginePlugin *plugin : lstPlugin) {
        mShortUrlServer->addItem(plugin->pluginName(), plugin->engineName());
    }

    connect(mShortUrlServer, &QComboBox::activated, this, &InsertShorturlConfigureWidget::slotChanged);
    loadConfig();
}

InsertShorturlConfigureWidget::~InsertShorturlConfigureWidget() = default;

void InsertShorturlConfigureWidget::slotChanged()
{
    mChanged = true;
}

void InsertShorturlConfigureWidget::loadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
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
        KConfigGroup grp(KSharedConfig::openConfig(), QLatin1StringView(myConfigGroupName));
        grp.writeEntry("EngineName", mShortUrlServer->itemData(mShortUrlServer->currentIndex()).toString());
        grp.sync();
    }
}

#include "moc_insertshorturlconfigurewidget.cpp"
