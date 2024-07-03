/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapwidget.h"
#include "imapfoldercompletionplugin_debug.h"
#include "selectimapfolderdialog.h"
#include "selectimaplineedit.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>

#include <KPluginFactory>
K_PLUGIN_CLASS_WITH_JSON(SelectImapWidget, "imapfoldercompletion.json")

SelectImapWidget::SelectImapWidget(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractMoveImapFolderWidget(parent)
    , mToolButton(new QToolButton(this))
    , mLineEdit(new SelectImapLineEdit(this))
{
    auto layout = new QHBoxLayout(this);
    layout->setObjectName(QLatin1StringView("mainlayout"));
    layout->setContentsMargins({});
    mLineEdit->setObjectName(QLatin1StringView("lineedit"));
    layout->addWidget(mLineEdit);

    mToolButton->setText(QStringLiteral("…"));
    mToolButton->setObjectName(QLatin1StringView("toolbutton"));
    mToolButton->setToolTip(i18nc("@info:tooltip", "Select IMAP folder"));
    mToolButton->hide();
    layout->addWidget(mToolButton);
    connect(mToolButton, &QToolButton::clicked, this, &SelectImapWidget::slotOpenSelectImapFolder);
}

SelectImapWidget::~SelectImapWidget()
{
    delete mSelectImapFolderDialog;
}

void SelectImapWidget::setText(const QString &str)
{
    mLineEdit->setText(str);
}

QString SelectImapWidget::text() const
{
    return mLineEdit->text();
}

void SelectImapWidget::setSieveImapAccountSettings(const KSieveCore::SieveImapAccountSettings &account)
{
    mAccount = account;
    if (mAccount.isValid()) {
        mToolButton->show();
        mLineEdit->setSieveImapAccountSettings(account);
        mLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Click on button for selecting folder…"));
    } else {
        qCDebug(IMAPFOLDERCOMPLETIONPLUGIN_LOG) << "Account is not defined";
    }
}

SelectImapFolderDialog *SelectImapWidget::selectFolderDialog()
{
    if (mSelectImapFolderDialog.isNull()) {
        mSelectImapFolderDialog = new SelectImapFolderDialog(mAccount, this);
        mSelectImapFolderDialog->setModal(true);
    }
    return mSelectImapFolderDialog;
}

void SelectImapWidget::slotOpenSelectImapFolder()
{
    QPointer<SelectImapFolderDialog> dlg(selectFolderDialog());
    if (dlg->exec()) {
        mLineEdit->setText(dlg->selectedFolderName());
    }
    // Don't delete it.
}

#include "selectimapwidget.moc"

#include "moc_selectimapwidget.cpp"
