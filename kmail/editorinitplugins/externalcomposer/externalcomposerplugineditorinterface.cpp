/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

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

#include "externalcomposerplugineditorinterface.h"
#include <KPIMTextEdit/RichTextComposer>
#include <KSharedConfig>
#include <KConfigGroup>

ExternalComposerPluginEditorInterface::ExternalComposerPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInitInterface(parent)
{
}

ExternalComposerPluginEditorInterface::~ExternalComposerPluginEditorInterface()
{
}

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
    KConfigGroup group = config->group(QStringLiteral("External Composer"));
    mEnabled = group.readEntry("Enabled", false);
    mExternalComposerPath = group.readEntry("ComposerPath", QString());
}
