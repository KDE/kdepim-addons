/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaichataddressbookplugin.h"
// #include "currentdatetimetoolplugindialog.h"
// #include "currentdatetimetoolpluginjob.h"
// #include "currentdatetimetoolpluginutils.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <QPointer>
K_PLUGIN_CLASS_WITH_JSON(KAIChatAddressBookPlugin, "kaichat_addressbook.json")

using namespace Qt::Literals::StringLiterals;
KAIChatAddressBookPlugin::KAIChatAddressBookPlugin(QObject *parent, const QVariantList &)
    : TextAutoGenerateTextToolPlugin{parent}
{
#if 0	
    mToolNameId = "current_date_time_tool"_ba;
    {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
        prop.setDescription(kli18n("The Current Date Time"));
        prop.setName(u"currentdatetime"_s);
        prop.setTypeElements({KAIChatAddressBookPluginUtils::convertDateTimeEnumToString(KAIChatAddressBookPluginUtils::Date),
                              KAIChatAddressBookPluginUtils::convertDateTimeEnumToString(KAIChatAddressBookPluginUtils::Time),
                              KAIChatAddressBookPluginUtils::convertDateTimeEnumToString(KAIChatAddressBookPluginUtils::DateTime)});
        mProperties.append(prop);
    }
#endif
}

KAIChatAddressBookPlugin::~KAIChatAddressBookPlugin() = default;

QString KAIChatAddressBookPlugin::displayName() const
{
    return i18n("Get Current Date Time");
}

QString KAIChatAddressBookPlugin::description() const
{
    return i18n("Use this tool to get current date time");
}

void KAIChatAddressBookPlugin::showConfigureDialog(QWidget *parent)
{
#if 0
    auto dlg = KAIChatAddressBookPluginDialog(this, parent);
    dlg.exec();
#endif
}

void KAIChatAddressBookPlugin::callTools(const QByteArray &chatId,
                                         const QByteArray &uuid,
                                         const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info)
{
#if 0	
    for (const auto &i : info) {
        auto job = new KAIChatAddressBookPluginJob(this);
        initializeJob(job, chatId, uuid, i);
        job->start();
    }
#endif
}

#include "kaichataddressbookplugin.moc"
#include "moc_kaichataddressbookplugin.cpp"
