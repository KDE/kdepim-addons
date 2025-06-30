/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerplugineditorinterface.h"
using namespace Qt::Literals::StringLiterals;

#include <KConfigGroup>
#include <KPIMTextEdit/RichTextComposer>
#include <KSharedConfig>

ExternalComposerPluginEditorInterface::ExternalComposerPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInitInterface(parent)
{
}

ExternalComposerPluginEditorInterface::~ExternalComposerPluginEditorInterface() = default;

bool ExternalComposerPluginEditorInterface::exec()
{
    if (mEnabled) {
        richTextEditor()->setUseExternalEditor(mEnabled);
        richTextEditor()->setExternalEditorPath(mExternalComposerPath);
    }
    return true;
}

void ExternalComposerPluginEditorInterface::reloadConfig()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup group = config->group(u"External Composer"_s);
    mEnabled = group.readEntry("Enabled", false);
    mExternalComposerPath = group.readEntry("ComposerPath", QString());
}

#include "moc_externalcomposerplugineditorinterface.cpp"
