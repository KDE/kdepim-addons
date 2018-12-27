/*
   Copyright (C) 2013-2019 Montel Laurent <montel@kde.org>

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

#include "adblockaddsubscriptiondialog.h"
#include "adblockshowlistdialog.h"
#include "adblockutil.h"

#include <KLocalizedString>

#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QToolButton>
#include <QPointer>

using namespace AdBlock;
AdBlockAddSubscriptionDialog::AdBlockAddSubscriptionDialog(const QStringList &excludeList, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Add subscription"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QWidget *w = new QWidget;
    QHBoxLayout *lay = new QHBoxLayout;
    lay->setMargin(0);
    QLabel *lab = new QLabel(i18n("Select List:"), this);
    lab->setObjectName(QStringLiteral("listsubscriptionlabel"));
    lay->addWidget(lab);

    mListSubscription = new QComboBox(this);
    mListSubscription->setObjectName(QStringLiteral("listsubscriptioncombobox"));
    lay->addWidget(mListSubscription);

    mShowList = new QToolButton(this);
    mShowList->setToolTip(i18n("Show List"));
    mShowList->setObjectName(QStringLiteral("showlisttoolbutton"));
    mShowList->setIcon(QIcon::fromTheme(QStringLiteral("document-preview")));
    lay->addWidget(mShowList);
    connect(mShowList, &QToolButton::clicked, this, &AdBlockAddSubscriptionDialog::slotShowList);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("listsubscriptionbuttonBox"));
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdBlockAddSubscriptionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdBlockAddSubscriptionDialog::reject);

    w->setLayout(lay);
    mainLayout->addWidget(w);
    mainLayout->addWidget(buttonBox);
    initializeList(excludeList);
}

AdBlockAddSubscriptionDialog::~AdBlockAddSubscriptionDialog()
{
}

void AdBlockAddSubscriptionDialog::initializeList(const QStringList &excludeList)
{
    QMapIterator<QString, QString> i(AdBlock::AdblockUtil::listSubscriptions());
    while (i.hasNext()) {
        i.next();
        if (!excludeList.contains(i.key())) {
            mListSubscription->addItem(i.key(), i.value());
        }
    }
}

void AdBlockAddSubscriptionDialog::selectedList(QString &name, QString &url)
{
    name = mListSubscription->currentText();
    url = mListSubscription->itemData(mListSubscription->currentIndex()).toString();
}

void AdBlockAddSubscriptionDialog::slotShowList()
{
    const QString url = mListSubscription->itemData(mListSubscription->currentIndex()).toString();
    if (!url.isEmpty()) {
        QPointer<AdBlockShowListDialog> dlg = new AdBlockShowListDialog(false, this);
        dlg->setListName(mListSubscription->currentText());
        dlg->setAdBlockListPath(QString(), url);
        dlg->exec();
        delete dlg;
    }
}
