/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QObject>

class EventEditTest : public QObject
{
    Q_OBJECT
public:
    explicit EventEditTest(QObject *parent = nullptr);

private Q_SLOTS:
    void shouldHaveDefaultValuesOnCreation();
    void shouldEmitCollectionChanged();
    void shouldEmitMessageChanged();
    void shouldNotEmitWhenCollectionIsNotChanged();
    void shouldNotEmitWhenMessageIsNotChanged();
    void shouldHideWidgetWhenPressEnter();
    void shouldEmitEventWhenPressEnter();
    void shouldSaveCollectionSettingsWhenCloseWidget();
    void shouldSaveCollectionSettings();
    void shouldHideWidgetWhenPressEscape();
    void shouldHideWidgetWhenSaveClicked();
    void shouldEventHasCorrectSubject();
    void shouldSelectLineWhenPutMessage();
    void shouldHaveCorrectStartEndDateTime();
    void shouldSaveCollectionSettingsWhenDeleteWidget();
    void shouldNotEmitCreateEventWhenDateIsInvalid();
    void shouldSetFocusWhenWeCallTodoEdit();
    void shouldEnsureEndDateIsNotBeforeStartDate();
    void shouldEnabledSaveOpenEditorButton();
    void shouldUpdateStartEndDateWhenReopenIt();
    void shouldDisabledSaveOpenEditorButtonWhenCollectionComboBoxIsEmpty();
};
