/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaichataddressbookplugin.h"
#include "kaichataddressbookplugindialog.h"
#include "kaichataddressbookpluginjob.h"
#include "kaichataddressbookpluginutils.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <QPointer>
K_PLUGIN_CLASS_WITH_JSON(KAIChatAddressBookPlugin, "kaichat_addressbook.json")

using namespace Qt::Literals::StringLiterals;
KAIChatAddressBookPlugin::KAIChatAddressBookPlugin(QObject *parent, const QVariantList &)
    : TextAutoGenerateTextToolPlugin{parent}
{
    mToolNameId = "addressbook_plugin"_ba;
    {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
        prop.setDescription(kli18n("AddressBook info"));
        prop.setName(u"addressbookinfo"_s);
        prop.setTypeElements({KAIChatAddressBookPluginUtils::convertAddressBookEnumToString(KAIChatAddressBookPluginUtils::Email)});
        mProperties.append(prop);
    }
}

KAIChatAddressBookPlugin::~KAIChatAddressBookPlugin() = default;

QString KAIChatAddressBookPlugin::displayName() const
{
    return i18n("Get email address");
}

QString KAIChatAddressBookPlugin::description() const
{
    return i18n("Use this tool to get email from akonadi database");
}

void KAIChatAddressBookPlugin::showConfigureDialog(QWidget *parent)
{
    auto dlg = KAIChatAddressBookPluginDialog(this, parent);
    dlg.exec();
}

void KAIChatAddressBookPlugin::callTools(const QByteArray &chatId,
                                         const QByteArray &uuid,
                                         const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info)
{
    for (const auto &i : info) {
        auto job = new KAIChatAddressBookPluginJob(this);
        initializeJob(job, chatId, uuid, i);
        job->start();
    }
}

#include "kaichataddressbookplugin.moc"
#include "moc_kaichataddressbookplugin.cpp"
