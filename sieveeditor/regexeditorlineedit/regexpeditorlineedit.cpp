/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "regexpeditorlineedit.h"
#include "regexpeditorlineeditplugin_debug.h"
#include <KPluginFactory>

#include <KLocalizedString>
#include <KServiceTypeTrader>
#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

#include <KTextWidgets/kregexpeditorinterface.h>

K_PLUGIN_CLASS_WITH_JSON(RegexpEditorLineEdit, "regexepeditorlineedit.json")
struct InfoRegExp {
    enum RegexpEditorStatus {
        Unknown = 0,
        Installed,
        NotInstalled,
    };
    RegexpEditorStatus status = Unknown;
    QDialog *mEditorDialog = nullptr;
};

Q_GLOBAL_STATIC(InfoRegExp, s_regexpeditorinstalled)

RegexpEditorLineEdit::RegexpEditorLineEdit(QWidget *parent, const QList<QVariant> &)
    : KSieveUi::AbstractRegexpEditorLineEdit(parent)
{
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mLineEdit = new QLineEdit(this);
    connect(mLineEdit, &QLineEdit::textChanged, this, &RegexpEditorLineEdit::textChanged);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);

    mRegExpEditorButton = new QToolButton(this);
    mRegExpEditorButton->setText(i18n("..."));
    mRegExpEditorButton->setObjectName(QStringLiteral("regexpbutton"));
    mRegExpEditorButton->setToolTip(i18n("Create Regular Expression"));
    mainLayout->addWidget(mRegExpEditorButton);
    // Disable for the moment until we fix kregexeditor
    s_regexpeditorinstalled->status = InfoRegExp::NotInstalled;
    if (s_regexpeditorinstalled->status == InfoRegExp::Unknown) {
        if (KServiceTypeTrader::self()->query(QStringLiteral("KRegExpEditor/KRegExpEditor")).isEmpty()) {
            s_regexpeditorinstalled->status = InfoRegExp::NotInstalled;
        } else {
            s_regexpeditorinstalled->status = InfoRegExp::Installed;
        }
    }
    if (s_regexpeditorinstalled->status == InfoRegExp::Installed) {
        connect(mRegExpEditorButton, &QToolButton::clicked, this, &RegexpEditorLineEdit::slotOpenRegexpEditor);
    } else {
        qCDebug(REGEXPEDITORLINEEDITPLUGIN_LOG) << "KRegExpEditor is not installed on system.";
    }
    // Hidden by default
    mRegExpEditorButton->setVisible(false);
}

RegexpEditorLineEdit::~RegexpEditorLineEdit()
{
}

void RegexpEditorLineEdit::slotOpenRegexpEditor()
{
    if (!s_regexpeditorinstalled->mEditorDialog) {
        QString error;

        s_regexpeditorinstalled->mEditorDialog =
            KServiceTypeTrader::createInstanceFromQuery<QDialog>(QStringLiteral("KRegExpEditor/KRegExpEditor"), this, this, {}, {}, &error);
        if (!s_regexpeditorinstalled->mEditorDialog) {
            qCWarning(REGEXPEDITORLINEEDITPLUGIN_LOG) << " Impossible to create regexpeditor " << error;
            return;
        }
    }
#if 0
    KRegExpEditorInterface *iface = qobject_cast<KRegExpEditorInterface *>(s_regexpeditorinstalled->mEditorDialog);
    Q_ASSERT(iface);   // This should not fail!

    // now use the editor.
    iface->setRegExp(mLineEdit->text());

    if (s_regexpeditorinstalled->mEditorDialog->exec() == QDialog::Accepted) {
        mLineEdit->setText(iface->regExp());
    }
#else
    qCWarning(REGEXPEDITORLINEEDITPLUGIN_LOG) << "KRegExpEditorInterface is deprecated. Need to adapt KRegExpEditor first ";
#endif
}

void RegexpEditorLineEdit::switchToRegexpEditorLineEdit(bool regexpEditor)
{
    if (s_regexpeditorinstalled->status == InfoRegExp::Installed) {
        mRegExpEditorButton->setVisible(regexpEditor);
    }
}

void RegexpEditorLineEdit::setCode(const QString &str)
{
    mLineEdit->setText(str);
}

QString RegexpEditorLineEdit::code() const
{
    return mLineEdit->text();
}

void RegexpEditorLineEdit::setClearButtonEnabled(bool b)
{
    mLineEdit->setClearButtonEnabled(b);
}

void RegexpEditorLineEdit::setPlaceholderText(const QString &str)
{
    mLineEdit->setPlaceholderText(str);
}

#include "regexpeditorlineedit.moc"
