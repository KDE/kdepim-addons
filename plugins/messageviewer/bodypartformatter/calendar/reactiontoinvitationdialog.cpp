/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "reactiontoinvitationdialog.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KPIMTextEdit/PlainTextEditor>
#include <KPIMTextEdit/PlainTextEditorWidget>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ReactionToInvitationDialog::ReactionToInvitationDialog(QWidget *parent)
    : QDialog(parent)
    , mPlainTextEditor(new KPIMTextEdit::PlainTextEditorWidget(this))
{
    auto layout = new QVBoxLayout(this);
    layout->setObjectName(QStringLiteral("layout"));

    QLabel *label = new QLabel(i18n("Comment:"), this);
    label->setObjectName(QStringLiteral("label"));
    layout->addWidget(label);

    mPlainTextEditor->setObjectName(QStringLiteral("plaintexteditor"));
    layout->addWidget(mPlainTextEditor);
    connect(mPlainTextEditor->editor(), &KPIMTextEdit::PlainTextEditor::textChanged, this, &ReactionToInvitationDialog::slotTextChanged);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    layout->addWidget(buttonBox);
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ReactionToInvitationDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ReactionToInvitationDialog::reject);
    readConfig();
}

ReactionToInvitationDialog::~ReactionToInvitationDialog()
{
    disconnect(mPlainTextEditor->editor(), &KPIMTextEdit::PlainTextEditor::textChanged, this, &ReactionToInvitationDialog::slotTextChanged);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), "ReactionToInvitationDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void ReactionToInvitationDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "ReactionToInvitationDialog");
    group.writeEntry("Size", size());
    group.sync();
}
