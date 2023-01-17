/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/CustomToolsViewInterface>
class KActionCollection;
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
namespace TextTranslator
#else
namespace PimCommonTextTranslator
#endif
{
class TranslatorWidget;
}
class TranslatorView : public PimCommon::CustomToolsViewInterface
{
    Q_OBJECT
public:
    explicit TranslatorView(KActionCollection *ac, QWidget *parent);
    ~TranslatorView() override;
    KToggleAction *action() const override;

    void setText(const QString &text) override;

private:
    void slotActivateTranslator(bool state);
    void createAction(KActionCollection *ac);
    KToggleAction *mAction = nullptr;
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
    TextTranslator::TranslatorWidget *const mTranslatorWidget;
#else
    PimCommonTextTranslator::TranslatorWidget *const mTranslatorWidget;
#endif
};
