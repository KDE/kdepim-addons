/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

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
namespace {
static const char myConfigGroupName[] = "ShortUrl";
}
InsertShorturlConfigureWidget::InsertShorturlConfigureWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

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

    connect(mShortUrlServer, qOverload<int>(&QComboBox::activated), this, &InsertShorturlConfigureWidget::slotChanged);
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
    KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
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
        KConfigGroup grp(KSharedConfig::openConfig(), myConfigGroupName);
        grp.writeEntry("EngineName", mShortUrlServer->itemData(mShortUrlServer->currentIndex()).toString());
        grp.sync();
    }
}
