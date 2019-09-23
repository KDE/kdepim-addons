/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#ifndef QUICKTEXTMENU_H
#define QUICKTEXTMENU_H

#include <QObject>
class QMenu;
namespace MessageComposer {
class PluginComposerInterface;
}
class QuickTextMenu : public QObject
{
    Q_OBJECT
public:
    explicit QuickTextMenu(QWidget *parentWidget, QObject *parent = nullptr);
    ~QuickTextMenu();
    QMenu *menu() const;

    void setPluginComposerInterface(MessageComposer::PluginComposerInterface *composerInterface);

Q_SIGNALS:
    void insertText(const QString &str);

private:
    void initializeMenu();
    void insertNamesAttachment();
    void insertToEmails();
    void insertCcEmails();
    void insertFromEmails();
    void insertNamesAndSizesOfAttachment();
    void insertSubject();
    void insertShortDate();
    void insertLongDate();
    void insertShortTime();
    void insertLongTime();
    void insertDayOfWeek();
    QWidget *mParentWidget = nullptr;
    QMenu *mMenu = nullptr;
    MessageComposer::PluginComposerInterface *mComposerInterface = nullptr;
};

#endif // QUICKTEXTMENU_H
