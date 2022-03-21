/*
  SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class NoteEditTest : public QObject
{
    Q_OBJECT
public:
    NoteEditTest();

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
    void shouldEmitNoteWhenPressEnter();
    void shouldEmitNotEmitNoteWhenTextIsEmpty();
    void shouldNoteHasCorrectSubject();
    void shouldClearAllWhenCloseWidget();
    void shouldEmitCollectionChangedWhenCurrentCollectionWasChanged();
    void shouldClearLineAfterEmitNewNote();
    void shouldEmitCorrectCollection();
    void shouldHideWidgetWhenClickOnCloseButton();
    void shouldHideWidgetWhenPressEscape();
    void shouldHideWidgetWhenSaveClicked();
    void shouldSaveCollectionSettings();
    void shouldSaveCollectionSettingsWhenCloseWidget();
    void shouldNotEmitNoteWhenMessageIsNull();
    void shouldHaveLineEditFocus();
    void shouldEmitNotEmitNoteWhenTextTrimmedIsEmpty();
    void shouldSaveCollectionSettingsWhenDeleteWidget();
    void shouldSetFocusWhenWeCallNoteEdit();
    void shouldShouldEnabledSaveEditorButton();
};
