/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
