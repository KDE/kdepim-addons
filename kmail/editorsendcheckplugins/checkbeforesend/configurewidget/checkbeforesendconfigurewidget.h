/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#ifndef CHECKBEFORESENDCONFIGUREWIDGET_H
#define CHECKBEFORESENDCONFIGUREWIDGET_H

#include <QWidget>
#include <MessageComposer/PluginEditorCheckBeforeSendConfigureWidget>

class QCheckBox;
class CheckBeforeSendConfigureWidget : public MessageComposer::PluginEditorCheckBeforeSendConfigureWidget
{
    Q_OBJECT
public:
    explicit CheckBeforeSendConfigureWidget(QWidget *parent = nullptr);
    ~CheckBeforeSendConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    QCheckBox *mCheckPlainTextMail = nullptr;
    QCheckBox *mCheckMailTransport = nullptr;
    QCheckBox *mCheckDuplicateEmailsAddresses = nullptr;
    QCheckBox *mCheckSendAttachments = nullptr;
};

#endif // CHECKBEFORESENDCONFIGUREWIDGET_H
