/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockaddsubscriptiondialog.h"
#include "adblockshowlistdialog.h"
#include "adblockutil.h"

#include <KLocalizedString>

#include <QComboBox>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPointer>
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>

using namespace AdBlock;
AdBlockAddSubscriptionDialog::AdBlockAddSubscriptionDialog(const QStringList &excludeList, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Add subscription"));
    auto mainLayout = new QVBoxLayout(this);

    auto w = new QWidget;
    auto lay = new QHBoxLayout;
    lay->setContentsMargins({});
    auto lab = new QLabel(i18n("Select List:"), this);
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

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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

AdBlockAddSubscriptionDialog::~AdBlockAddSubscriptionDialog() = default;

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
