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

#ifndef AKREGATORPLUGINTRANSLATORINTERFACE_H
#define AKREGATORPLUGINTRANSLATORINTERFACE_H

#include <messageviewer/viewerplugininterface.h>
class KActionCollection;
namespace PimCommon
{
class TranslatorWidget;
}
namespace MessageViewer
{
class AkregatorPluginTranslatorInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit AkregatorPluginTranslatorInterface(KActionCollection *ac, QWidget *parent = Q_NULLPTR);
    ~AkregatorPluginTranslatorInterface();

    void setText(const QString &text) Q_DECL_OVERRIDE;
    QAction *action() const Q_DECL_OVERRIDE;
    void showWidget() Q_DECL_OVERRIDE;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const Q_DECL_OVERRIDE;

private:
    void createAction(KActionCollection *ac);
    QAction *mAction;
    PimCommon::TranslatorWidget *mTranslatorWidget;

};
}
#endif // AKREGATORPLUGINTRANSLATORINTERFACE_H
