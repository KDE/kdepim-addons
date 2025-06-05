/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateanswerseditordialog.h"
#include <KLocalizedString>
#include <QVBoxLayout>

AutoGenerateAnswersEditorDialog::AutoGenerateAnswersEditorDialog(QWidget *parent)
    : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    // TODO
}

AutoGenerateAnswersEditorDialog::~AutoGenerateAnswersEditorDialog()
{
}
