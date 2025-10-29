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
        prop.setTypeElements({KAIChatAddressBookPluginUtils::convertAddressBookEnumToString(KAIChatAddressBookPluginUtils::Email),
                              KAIChatAddressBookPluginUtils::convertAddressBookEnumToString(KAIChatAddressBookPluginUtils::Birthday),
                              KAIChatAddressBookPluginUtils::convertAddressBookEnumToString(KAIChatAddressBookPluginUtils::Address)});
        mProperties.append(prop);
    }
    {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
        prop.setDescription(kli18n("Name of user"));
        prop.setName(u"username"_s);
        mProperties.append(prop);
    }
}

KAIChatAddressBookPlugin::~KAIChatAddressBookPlugin() = default;

QString KAIChatAddressBookPlugin::displayName() const
{
    return i18n("Get Info From AddressBook");
}

QString KAIChatAddressBookPlugin::description() const
{
    return i18n("Use this tool to get user info from akonadi database");
}

QString KAIChatAddressBookPlugin::iconName() const
{
    return u"office-address-book"_s;
}

void KAIChatAddressBookPlugin::showConfigureDialog(QWidget *parent)
{
    auto dlg = KAIChatAddressBookPluginDialog(this, parent);
    dlg.exec();
}

TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *KAIChatAddressBookPlugin::callTool()
{
    return new KAIChatAddressBookPluginJob(this);
}

#include "kaichataddressbookplugin.moc"
#include "moc_kaichataddressbookplugin.cpp"
