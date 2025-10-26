/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaichatcalendarplugin.h"
#include "kaichataddressbookplugindialog.h"
#include "kaichataddressbookpluginjob.h"
#include "kaichataddressbookpluginutils.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <QPointer>
K_PLUGIN_CLASS_WITH_JSON(KAIChatCalendarPlugin, "kaichat_addressbook.json")

using namespace Qt::Literals::StringLiterals;
KAIChatCalendarPlugin::KAIChatCalendarPlugin(QObject *parent, const QVariantList &)
    : TextAutoGenerateTextToolPlugin{parent}
{
    mToolNameId = "addressbook_plugin"_ba;
    {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
        prop.setDescription(kli18n("AddressBook info"));
        prop.setName(u"addressbookinfo"_s);
        prop.setTypeElements({KAIChatCalendarPluginUtils::convertAddressBookEnumToString(KAIChatCalendarPluginUtils::Email),
                              KAIChatCalendarPluginUtils::convertAddressBookEnumToString(KAIChatCalendarPluginUtils::Birthday)});
        mProperties.append(prop);
    }
    {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
        prop.setDescription(kli18n("Name of user"));
        prop.setName(u"username"_s);
        mProperties.append(prop);
    }
}

KAIChatCalendarPlugin::~KAIChatCalendarPlugin() = default;

QString KAIChatCalendarPlugin::displayName() const
{
    return i18n("Get Info From AddressBook");
}

QString KAIChatCalendarPlugin::description() const
{
    return i18n("Use this tool to get user info from akonadi database");
}

void KAIChatCalendarPlugin::showConfigureDialog(QWidget *parent)
{
    auto dlg = KAIChatCalendarPluginDialog(this, parent);
    dlg.exec();
}

void KAIChatCalendarPlugin::callTools(const QByteArray &chatId,
                                      const QByteArray &uuid,
                                      const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info)
{
    for (const auto &i : info) {
        auto job = new KAIChatCalendarPluginJob(this);
        initializeJob(job, chatId, uuid, i);
        job->start();
    }
}

#include "kaichataddressbookplugin.moc"
#include "moc_kaichatcalendarplugin.cpp"
