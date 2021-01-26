/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef EXTERNALCOMPOSERCONFIGUREWIDGET_H
#define EXTERNALCOMPOSERCONFIGUREWIDGET_H

#include <MessageComposer/PluginEditorInitConfigureWidget>
#include <QWidget>
class QCheckBox;
class KUrlRequester;
class ExternalComposerConfigureWidget : public MessageComposer::PluginEditorInitConfigureWidget
{
    Q_OBJECT
public:
    explicit ExternalComposerConfigureWidget(QWidget *parent = nullptr);
    ~ExternalComposerConfigureWidget() override;

    void loadSettings() override;
    void saveSettings() override;
    void resetSettings() override;

private:
    QCheckBox *mExternalEditorCheck = nullptr;
    KUrlRequester *mEditorRequester = nullptr;
};

#endif // EXTERNALCOMPOSERCONFIGUREWIDGET_H
