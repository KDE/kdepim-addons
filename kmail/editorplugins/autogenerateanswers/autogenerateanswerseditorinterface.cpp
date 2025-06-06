/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateanswerseditorinterface.h"
#include "autogenerateanswerseditordialog.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <QMenu>
#include <TextAutoGenerateText/TextAutoGenerateDialog>

AutoGenerateAnswersEditorInterface::AutoGenerateAnswersEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

AutoGenerateAnswersEditorInterface::~AutoGenerateAnswersEditorInterface() = default;

void AutoGenerateAnswersEditorInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18nc("@action", "Autogenerate Answer"), this);
    ac->addAction(QStringLiteral("quick_answer"), action);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Edit);
    setActionType(type);
    auto menu = new QMenu(parentWidget());
    auto act = menu->addAction(i18nc("@action", "Summary Text"));
    connect(act, &QAction::triggered, this, [this]() {
        mAnswerType = AnswerType::SummaryText;
        Q_EMIT emitPluginActivated(this);
    });

    act = menu->addAction(i18nc("@action", "Correct Text"));
    connect(act, &QAction::triggered, this, [this]() {
        mAnswerType = AnswerType::FixTypo;
        Q_EMIT emitPluginActivated(this);
    });

    act = menu->addAction(i18nc("@action", "Quick Answer"));
    connect(act, &QAction::triggered, this, [this]() {
        mAnswerType = AnswerType::QuickAnswer;
        Q_EMIT emitPluginActivated(this);
    });
    action->setMenu(menu);
}

void AutoGenerateAnswersEditorInterface::exec()
{
    switch (mAnswerType) {
    case AnswerType::Unknown:
        break;
    case AnswerType::SummaryText:
        break;
    case AnswerType::QuickAnswer:
        break;
    case AnswerType::FixTypo:
        break;
    }

    // TODO
}

#include "moc_autogenerateanswerseditorinterface.cpp"
