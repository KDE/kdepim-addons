/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#ifndef VIEWERPLUGINTRANSLATORINTERFACE_H
#define VIEWERPLUGINTRANSLATORINTERFACE_H

#include <MessageViewer/ViewerPluginInterface>
class KActionCollection;
namespace PimCommon {
class TranslatorWidget;
}
namespace MessageViewer {
class ViewerPluginTranslatorInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginTranslatorInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginTranslatorInterface() override;

    void setText(const QString &text) override;
    QList<QAction *> actions() const override;
    void showWidget() override;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

private:
    PimCommon::TranslatorWidget *widget();
    void createAction(KActionCollection *ac);
    QList<QAction *> mAction;
    PimCommon::TranslatorWidget *mTranslatorWidget = nullptr;
};
}
#endif // VIEWERPLUGINTRANSLATORINTERFACE_H
