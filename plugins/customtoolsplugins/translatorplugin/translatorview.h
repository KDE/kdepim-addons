/*
   SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/CustomToolsViewInterface>
class KActionCollection;
namespace PimCommon
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
    PimCommon::TranslatorWidget *const mTranslatorWidget;
};
