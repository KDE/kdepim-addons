/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kaichatcalendarplugin.h"
#include "kaichatcalendarplugindialog.h"
#include "kaichatcalendarpluginjob.h"
#include "kaichatcalendarpluginutils.h"
#include <KLocalizedString>
#include <KPluginFactory>
#include <QPointer>
K_PLUGIN_CLASS_WITH_JSON(KAIChatCalendarPlugin, "kaichat_calendar.json")

using namespace Qt::Literals::StringLiterals;
KAIChatCalendarPlugin::KAIChatCalendarPlugin(QObject *parent, const QVariantList &)
    : TextAutoGenerateTextToolPlugin{parent}
{
    mToolNameId = "calendar_plugin"_ba;
    {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
        prop.setDescription(kli18n("calendar info"));
        prop.setName(u"calendarinfo"_s);
        prop.setTypeElements({KAIChatCalendarPluginUtils::convertCalendarEnumToString(KAIChatCalendarPluginUtils::Email)});
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
    return i18n("Get Info From calendar");
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

TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *KAIChatCalendarPlugin::callTool()
{
    return new KAIChatCalendarPluginJob(this);
}

#include "kaichatcalendarplugin.moc"
#include "moc_kaichatcalendarplugin.cpp"
