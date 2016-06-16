/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef SENDMAILPLUGININTERFACE_H
#define SENDMAILPLUGININTERFACE_H

#include <pimcommon/genericplugininterface.h>

class SendMailPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit SendMailPluginInterface(QObject *parent = Q_NULLPTR);
    ~SendMailPluginInterface();

    void exec() Q_DECL_OVERRIDE;
    void createAction(KActionCollection *ac) Q_DECL_OVERRIDE;
    void setCurrentItems(const Akonadi::Item::List &items) Q_DECL_OVERRIDE;
    PimCommon::GenericPluginInterface::RequireTypes requires() const Q_DECL_OVERRIDE;
    bool hasPopupMenuSupport() const Q_DECL_OVERRIDE;
    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotActivated();
    void slotSendMailError(const QString &error);
    void slotSendMails(const QStringList &emails);

private:
    Akonadi::Item::List mListItems;
    QAction *mAction;
};

#endif // SENDMAILPLUGININTERFACE_H
