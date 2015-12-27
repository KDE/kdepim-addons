/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ROT13PLUGINEDITOR_H
#define ROT13PLUGINEDITOR_H

#include <messagecomposer/plugineditor.h>

#include <messagecomposer/plugineditorinterface.h>
#include <QVariant>

class Rot13PluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit Rot13PluginEditor(QObject *parent = Q_NULLPTR, const QList<QVariant> & = QList<QVariant>());
    ~Rot13PluginEditor();

    MessageComposer::PluginEditorInterface *createInterface(KActionCollection *ac, QObject *parent = Q_NULLPTR) Q_DECL_OVERRIDE;
};

#endif // ROT13PLUGINEDITOR_H
