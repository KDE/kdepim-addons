/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownplugin.h"
#include "markdownconfiguredialog.h"
#include "markdowninterface.h"
#include <KLocalizedString>
#include <KPluginFactory>

#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(MarkdownPlugin, "kmail_markdownplugin.json")

MarkdownPlugin::MarkdownPlugin(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorConvertText(parent)
{
}

MarkdownPlugin::~MarkdownPlugin() = default;

MessageComposer::PluginEditorConvertTextInterface *MarkdownPlugin::createInterface(QObject *parent)
{
    auto interface = new MarkdownInterface(parent);
    connect(this, &MarkdownPlugin::configChanged, interface, &MarkdownInterface::reloadConfig);
    return interface;
}

bool MarkdownPlugin::hasConfigureDialog() const
{
    return true;
}

void MarkdownPlugin::showConfigureDialog(QWidget *parent)
{
    Q_UNUSED(parent)
    QPointer<MarkdownConfigureDialog> dlg = new MarkdownConfigureDialog(parent);
    if (dlg->exec()) {
        Q_EMIT configChanged();
    }
    delete dlg;
}

QString MarkdownPlugin::description() const
{
    return i18n("Generate HTML from markdown language.");
}

bool MarkdownPlugin::canWorkOnHtml() const
{
    return false;
}

bool MarkdownPlugin::hasStatusBarSupport() const
{
    return true;
}

bool MarkdownPlugin::hasPopupMenuSupport() const
{
    return true;
}

bool MarkdownPlugin::hasToolBarSupport() const
{
    return false;
}

#include "markdownplugin.moc"

#include "moc_markdownplugin.cpp"
