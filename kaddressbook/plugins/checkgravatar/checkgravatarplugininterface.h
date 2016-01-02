/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef CHECKGRAVATARPLUGININTERFACE_H
#define CHECKGRAVATARPLUGININTERFACE_H

#include <pimcommon/genericplugininterface.h>

class CheckGravatarPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit CheckGravatarPluginInterface(QObject *parent = Q_NULLPTR);
    ~CheckGravatarPluginInterface();

    void exec() Q_DECL_OVERRIDE;
    void createAction(KActionCollection *ac) Q_DECL_OVERRIDE;
    void setCurrentItems(const Akonadi::Item::List &items) Q_DECL_OVERRIDE;
    PimCommon::GenericPluginInterface::RequireTypes requires() const Q_DECL_OVERRIDE;
    bool hasPopupMenuSupport() const Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotActivated();
    void slotModifyContactFinished(KJob *job);
private:
    Akonadi::Item::List mListItems;
};

#endif // CHECKGRAVATARPLUGININTERFACE_H
