/*
   Copyright (C) 2016-2019 Montel Laurent <montel@kde.org>

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

#ifndef ZOOMTEXTPLUGINEDITOR_H
#define ZOOMTEXTPLUGINEDITOR_H

#include <messagecomposer/plugineditor.h>

#include <messagecomposer/plugineditorinterface.h>
#include <QVariant>

class ZoomTextPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit ZoomTextPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ZoomTextPluginEditor() override;

    MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
    Q_REQUIRED_RESULT bool hasStatusBarSupport() const override;
Q_SIGNALS:
    void zoomFactorChanged(int val);
};

#endif
