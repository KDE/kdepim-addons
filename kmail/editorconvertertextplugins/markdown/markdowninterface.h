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

#ifndef MARKDOWNINTERFACE_H
#define MARKDOWNINTERFACE_H

#include <QObject>
#include <QPointer>
#include <MessageComposer/PluginEditorConvertTextInterface>
class KActionCollection;
class MarkdownPreviewDialog;
class MarkdownInterface : public MessageComposer::PluginEditorConvertTextInterface
{
    Q_OBJECT
public:
    explicit MarkdownInterface(QObject *parent = nullptr);
    ~MarkdownInterface() override;
    void createAction(KActionCollection *ac) override;

    bool reformatText() override;
    MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus convertTextToFormat(MessageComposer::TextPart *textPart) override;

public Q_SLOTS:
    void reloadConfig() override;

private:
    void slotActivated();
    QAction *mAction = nullptr;
    QPointer<MarkdownPreviewDialog> mDialog;
};

#endif // MARKDOWNINTERFACE_H
