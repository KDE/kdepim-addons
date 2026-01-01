/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TodoEditTest : public QObject
{
    Q_OBJECT
public:
    TodoEditTest();

private Q_SLOTS:
    void shouldNotEmitWhenMessageIsNotChanged();
    void shouldHaveDefaultValuesOnCreation();
    void shouldEmitCollectionChanged();
    void shouldEmitMessageChanged();
    void shouldNotEmitWhenCollectionIsNotChanged();
    void shouldHaveSameValueAfterSet();
    void shouldHaveASubject();
    void shouldEmptySubjectWhenMessageIsNull();
    void shouldEmptySubjectWhenMessageHasNotSubject();
    void shouldSelectLineWhenPutMessage();
    void shouldEmitCollectionChangedWhenChangeComboboxItem();
    void shouldEmitTodoWhenPressEnter();
    void shouldEmitNotEmitTodoWhenTextIsEmpty();
    void shouldTodoHasCorrectSubject();
    void shouldClearAllWhenCloseWidget();
    void shouldEmitCollectionChangedWhenCurrentCollectionWasChanged();
    void shouldClearLineAfterEmitNewNote();
    void shouldEmitCorrectCollection();
    void shouldHideWidgetWhenClickOnCloseButton();
    void shouldHideWidgetWhenPressEscape();
    void shouldHideWidgetWhenSaveClicked();
    void shouldSaveCollectionSettings();
    void shouldSaveCollectionSettingsWhenCloseWidget();
    void shouldNotEmitTodoWhenMessageIsNull();
    void shouldHaveLineEditFocus();
    void shouldEmitNotEmitTodoWhenTextTrimmedIsEmpty();
    void shouldSaveCollectionSettingsWhenDeleteWidget();
    void shouldSetFocusWhenWeCallTodoEdit();
    void shouldShowMessageWidget();
    void shouldHideMessageWidget();
    void shouldHideMessageWidgetWhenAddNewMessage();
    void shouldHideMessageWidgetWhenCloseWidget();
    void shouldEnabledSaveOpenEditorButton();
    void shouldDisabledSaveOpenEditorButtonWhenCollectionComboBoxIsEmpty();
};
