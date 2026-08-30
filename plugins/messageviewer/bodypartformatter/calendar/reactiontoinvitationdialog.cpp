/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "reactiontoinvitationdialog.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
#include <TextCustomEditor/PlainTextEditor>
#include <TextCustomEditor/PlainTextEditorWidget>
using namespace Qt::Literals::StringLiterals;
namespace
{
const char myConfigReactionToInvitationDialog[] = "ReactionToInvitationDialog";
}
ReactionToInvitationDialog::ReactionToInvitationDialog(QWidget *parent)
    : QDialog(parent)
    , mPlainTextEditor(new TextCustomEditor::PlainTextEditorWidget(this))
{
    auto layout = new QVBoxLayout(this);
    layout->setObjectName("layout"_L1);

    auto label = new QLabel(i18nc("@label:textbox", "Comment:"), this);
    label->setObjectName("label"_L1);
    layout->addWidget(label);

    mPlainTextEditor->setObjectName("plaintexteditor"_L1);
    layout->addWidget(mPlainTextEditor);
    connect(mPlainTextEditor->editor(), &TextCustomEditor::PlainTextEditor::textChanged, this, &ReactionToInvitationDialog::slotTextChanged);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonbox"_L1);
    layout->addWidget(buttonBox);
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ReactionToInvitationDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ReactionToInvitationDialog::reject);
    readConfig();
}

ReactionToInvitationDialog::~ReactionToInvitationDialog()
{
    disconnect(mPlainTextEditor->editor(), &TextCustomEditor::PlainTextEditor::textChanged, this, &ReactionToInvitationDialog::slotTextChanged);
    writeConfig();
}

void ReactionToInvitationDialog::slotTextChanged()
{
    mOkButton->setEnabled(!mPlainTextEditor->editor()->document()->isEmpty());
}

QString ReactionToInvitationDialog::comment() const
{
    return mPlainTextEditor->toPlainText();
}

void ReactionToInvitationDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myConfigReactionToInvitationDialog), 600, 400);
}

void ReactionToInvitationDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigReactionToInvitationDialog));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_reactiontoinvitationdialog.cpp"
