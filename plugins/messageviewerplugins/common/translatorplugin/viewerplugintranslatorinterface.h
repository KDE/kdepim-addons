/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/ViewerPluginInterface>
class KActionCollection;
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
namespace TextTranslator
#else
namespace PimCommonTextTranslator
#endif
{
class TranslatorWidget;
}
namespace MessageViewer
{
class ViewerPluginTranslatorInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginTranslatorInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginTranslatorInterface() override;

    void setText(const QString &text) override;
    Q_REQUIRED_RESULT QList<QAction *> actions() const override;
    void showWidget() override;
    Q_REQUIRED_RESULT ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

private:
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
    Q_REQUIRED_RESULT TextTranslator::TranslatorWidget *widget();
#else
    Q_REQUIRED_RESULT PimCommonTextTranslator::TranslatorWidget *widget();
#endif
    void createAction(KActionCollection *ac);
    QList<QAction *> mAction;
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
    TextTranslator::TranslatorWidget *mTranslatorWidget = nullptr;
#else
    PimCommonTextTranslator::TranslatorWidget *mTranslatorWidget = nullptr;
#endif
};
}
