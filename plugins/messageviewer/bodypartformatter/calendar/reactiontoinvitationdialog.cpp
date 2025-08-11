/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

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
#include <TextCustomEditor/PlainTextEditor>
#include <TextCustomEditor/PlainTextEditorWidget>
namespace
{
const char myConfigReactionToInvitationDialog[] = "ReactionToInvitationDialog";
}
ReactionToInvitationDialog::ReactionToInvitationDialog(QWidget *parent)
    : QDialog(parent)
    , mPlainTextEditor(new TextCustomEditor::PlainTextEditorWidget(this))
{
    auto layout = new QVBoxLayout(this);
    layout->setObjectName(QLatin1StringView("layout"));

    auto label = new QLabel(i18nc("@label:textbox", "Comment:"), this);
    label->setObjectName(QLatin1StringView("label"));
    layout->addWidget(label);

    mPlainTextEditor->setObjectName(QLatin1StringView("plaintexteditor"));
    layout->addWidget(mPlainTextEditor);
    connect(mPlainTextEditor->editor(), &TextCustomEditor::PlainTextEditor::textChanged, this, &ReactionToInvitationDialog::slotTextChanged);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
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
    windowHandle()->resize(QSize(600, 400));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigReactionToInvitationDialog));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void ReactionToInvitationDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigReactionToInvitationDialog));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

#include "moc_reactiontoinvitationdialog.cpp"
