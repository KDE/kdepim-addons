/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ChangeCasePLUGINEDITOR_H
#define ChangeCasePLUGINEDITOR_H

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class ChangeCasePluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit ChangeCasePluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ChangeCasePluginEditor() override;

    MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif
