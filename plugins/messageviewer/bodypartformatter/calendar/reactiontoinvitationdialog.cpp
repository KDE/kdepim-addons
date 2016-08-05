/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "reactiontoinvitationdialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include "kpimtextedit/plaintexteditorwidget.h"

ReactionToInvitationDialog::ReactionToInvitationDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setObjectName(QStringLiteral("layout"));

    QLabel *label = new QLabel(i18n("Comment:"), this);
    label->setObjectName(QStringLiteral("label"));
    layout->addWidget(label);

    mPlainTextEditor = new KPIMTextEdit::PlainTextEditorWidget(this);
    mPlainTextEditor->setObjectName(QStringLiteral("plaintexteditor"));
    layout->addWidget(mPlainTextEditor);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    layout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ReactionToInvitationDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ReactionToInvitationDialog::reject);
    readConfig();
}

ReactionToInvitationDialog::~ReactionToInvitationDialog()
{
    writeConfig();
}

QString ReactionToInvitationDialog::comment() const
{
    return mPlainTextEditor->toPlainText();
}

void ReactionToInvitationDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ReactionToInvitationDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void ReactionToInvitationDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ReactionToInvitationDialog");
    group.writeEntry("Size", size());
    group.sync();
}
