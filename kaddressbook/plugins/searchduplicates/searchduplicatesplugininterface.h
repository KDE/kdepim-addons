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

#ifndef SEARCHDUPLICATESPLUGININTERFACE_H
#define SEARCHDUPLICATESPLUGININTERFACE_H

#include <pimcommon/genericplugininterface.h>

class SearchDuplicatesPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit SearchDuplicatesPluginInterface(QObject *parent = Q_NULLPTR);
    ~SearchDuplicatesPluginInterface();

    void exec() Q_DECL_OVERRIDE;
    void createAction(KActionCollection *ac) Q_DECL_OVERRIDE;
    void setCurrentItems(const Akonadi::Item::List &items) Q_DECL_OVERRIDE;
    PimCommon::GenericPluginInterface::RequireTypes requires() const Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotActivated();

private:
    Akonadi::Item::List mListItems;
};

#endif // SEARCHDUPLICATESPLUGININTERFACE_H
