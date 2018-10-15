/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#ifndef MARKDOWNPLUGIN_H
#define MARKDOWNPLUGIN_H

#include <MessageComposer/PluginEditorConvertText>

class MarkdownPlugin : public MessageComposer::PluginEditorConvertText
{
    Q_OBJECT
public:
    explicit MarkdownPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~MarkdownPlugin() override;

    MessageComposer::PluginEditorConvertTextInterface *createInterface(KActionCollection *ac, QObject *parent) override;

    bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;
    QString description() const override;
    bool canWorkOnHtml() const override;
    bool hasStatusBarSupport() const override;

Q_SIGNALS:
    void configChanged();
};

#endif // MARKDOWNPLUGIN_H
