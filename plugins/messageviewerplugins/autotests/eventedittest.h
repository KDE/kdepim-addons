/*
   Copyright (C) 2014-2018 Montel Laurent <montel@kde.org>

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

#ifndef EVENTEDITTEST_H
#define EVENTEDITTEST_H
#include <QObject>

class EventEditTest : public QObject
{
    Q_OBJECT
public:
    EventEditTest();

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

#endif // EVENTEDITTEST_H
