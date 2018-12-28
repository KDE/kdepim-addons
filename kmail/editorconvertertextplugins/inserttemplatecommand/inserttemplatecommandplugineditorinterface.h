/*
   Copyright (C) 2018-2019 Montel Laurent <montel@kde.org>

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

#ifndef INSERTTEMPLATECOMMANDPLUGINEDITORINTERFACE_H
#define INSERTTEMPLATECOMMANDPLUGINEDITORINTERFACE_H

#include <MessageComposer/PluginEditorConvertTextInterface>
class QToolButton;
namespace TemplateParser {
class TemplatesInsertCommandAction;
}
class InsertTemplateCommandPluginEditorInterface : public MessageComposer::PluginEditorConvertTextInterface
{
    Q_OBJECT
public:
    explicit InsertTemplateCommandPluginEditorInterface(QObject *parent = nullptr);
    ~InsertTemplateCommandPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    ConvertTextStatus convertTextToFormat(MessageComposer::TextPart *textPart) override;
    bool reformatText() override;
    void setInitialData(const MessageComposer::PluginEditorConverterInitialData &data) override;

private:
    void slotInsertCommand(const QString &cmd, int adjustCursor);
    void slotActivated();
    void slotOpenMenu();
    QString mCommand;
    int mAdjustCursor = 0;
    TemplateParser::TemplatesInsertCommandAction *mCommandAction = nullptr;
    QToolButton *mToolButton = nullptr;
};

#endif
