/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectlistwidget.h"
#include "kaddressbookmergelibprivate_debug.h"
#include <KLocalizedString>
#include <QLabel>
#include <QListWidget>
#include <QLocale>
#include <QVBoxLayout>
using namespace KABMergeContacts;
using namespace KContacts;

MergeContactSelectListWidget::MergeContactSelectListWidget(QWidget *parent)
    : QWidget(parent)
    , mTitle(new QLabel(this))
    , mSelectListWidget(new QListWidget(this))
    , mConflictType(MergeContacts::None)
{
    auto vbox = new QVBoxLayout(this);
    mTitle->setObjectName(QLatin1StringView("title"));
    vbox->addWidget(mTitle);
    mSelectListWidget->setObjectName(QLatin1StringView("listwidget"));
    vbox->addWidget(mSelectListWidget);
}

MergeContactSelectListWidget::~MergeContactSelectListWidget() = default;

void MergeContactSelectListWidget::setContacts(MergeContacts::ConflictInformation conflictType, const KContacts::Addressee::List &lst)
{
    mConflictType = conflictType;
    if (lst.isEmpty() || (conflictType == MergeContacts::None)) {
        return;
    }
    updateTitle();
    fillList(lst);
}

void MergeContactSelectListWidget::updateTitle()
{
    QString title;
    switch (mConflictType) {
    case MergeContacts::None:
        // qCWarning(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " MergeContacts::None used in updateTitle. It's a bug";
        // it's not possible.
        break;
    case MergeContacts::Birthday:
        title = Addressee::birthdayLabel();
        break;
    case MergeContacts::Geo:
        title = Addressee::geoLabel();
        break;
    case MergeContacts::Photo:
        title = Addressee::photoLabel();
        break;
    case MergeContacts::Logo:
        title = Addressee::logoLabel();
        break;
    case MergeContacts::Anniversary:
        title = i18nc("The wedding anniversary of a contact", "Anniversary");
        break;
    case MergeContacts::Name:
        title = Addressee::nameLabel();
        break;
    case MergeContacts::NickName:
        title = Addressee::nickNameLabel();
        break;
    case MergeContacts::Blog:
        title = i18n("Blog Feed");
        break;
    case MergeContacts::HomePage:
        title = QStringLiteral("HomePage");
        break;
    case MergeContacts::Organization:
        title = Addressee::organizationLabel();
        break;
    case MergeContacts::Profession:
        title = i18n("Profession");
        break;
    case MergeContacts::Title:
        title = Addressee::titleLabel();
        break;
    case MergeContacts::Departement:
        title = Addressee::departmentLabel();
        break;
    case MergeContacts::Office:
        title = i18n("Office");
        break;
    case MergeContacts::ManagerName:
        title = i18n("Manager");
        break;
    case MergeContacts::Assistant:
        title = i18n("Assistant");
        break;
    case MergeContacts::FreeBusy:
        title = QStringLiteral("FreeBusy");
        break;
    case MergeContacts::FamilyName:
        title = Addressee::familyNameLabel();
        break;
    case MergeContacts::PartnerName:
        title = i18n("Spouse");
        break;
    case MergeContacts::Keys:
        title = QStringLiteral("Keys");
        break;
    }

    mTitle->setText(title);
}

void MergeContactSelectListWidget::addItem(const QString &str, const QIcon &icon)
{
    if (str.isEmpty()) {
        auto item = new QListWidgetItem(mSelectListWidget);
        item->setFlags(Qt::NoItemFlags);
        item->setText(i18n("(Undefined)"));
        mSelectListWidget->addItem(item);
    } else {
        if (!icon.isNull()) {
            auto item = new QListWidgetItem(mSelectListWidget);
            item->setText(str);
            item->setIcon(icon);
            mSelectListWidget->addItem(item);
        } else {
            mSelectListWidget->addItem(str);
        }
    }
}

void MergeContactSelectListWidget::fillList(const KContacts::Addressee::List &lst)
{
    mSelectListWidget->clear();
    for (const Addressee &addr : lst) {
        switch (mConflictType) {
        case MergeContacts::None:
            break;
        case MergeContacts::Birthday: {
            const QDate birdthDt = addr.birthday().date();
            QString birdth;
            if (birdthDt.isValid()) {
                birdth = QLocale().toString(birdthDt);
            }
            addItem(birdth);
            break;
        }
        case MergeContacts::Geo: {
            const Geo geo = addr.geo();
            const QString str = QStringLiteral("%1-%2").arg(geo.latitude()).arg(geo.longitude());
            addItem(str);
            break;
        }
        case MergeContacts::Photo:
            // TODO fix when it's an url
            addItem(QString(), QIcon(QPixmap::fromImage(addr.photo().data())));
            break;
        case MergeContacts::Logo:
            // TODO fix when it's an url
            addItem(QString(), QIcon(QPixmap::fromImage(addr.logo().data())));
            break;
        case MergeContacts::Anniversary: {
            QString anniversary;
            const QDate anniversaryDt = QDate::fromString(addr.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Anniversary")), Qt::ISODate);
            if (anniversaryDt.isValid()) {
                anniversary = QLocale().toString(anniversaryDt);
            }
            addItem(anniversary);
            break;
        }
        case MergeContacts::Name:
            addItem(addr.name());
            break;
        case MergeContacts::NickName:
            addItem(addr.nickName());
            break;
        case MergeContacts::Blog: {
            const QString newBlog = addr.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("BlogFeed"));
            addItem(newBlog);
            break;
        }
        case MergeContacts::HomePage:
            addItem(addr.url().toString());
            break;
        case MergeContacts::Organization:
            addItem(addr.organization());
            break;
        case MergeContacts::Profession: {
            const QString newBlog = addr.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Profession"));
            addItem(newBlog);
            break;
        }
        case MergeContacts::Title:
            addItem(addr.title());
            break;
        case MergeContacts::Departement:
            addItem(addr.department());
            break;
        case MergeContacts::Office: {
            const QString newBlog = addr.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Office"));
            addItem(newBlog);
            break;
        }
        case MergeContacts::ManagerName: {
            const QString newBlog = addr.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-ManagersName"));
            addItem(newBlog);
            break;
        }
        case MergeContacts::Assistant: {
            const QString newBlog = addr.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-AssistantsName"));
            addItem(newBlog);
            break;
        }
        case MergeContacts::FreeBusy:
            // FIXME
            break;
        case MergeContacts::FamilyName:
            addItem(addr.familyName());
            break;
        case MergeContacts::PartnerName: {
            const QString newBlog = addr.custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-SpousesName"));
            addItem(newBlog);
            break;
        }
        case MergeContacts::Keys:
            // TODO
            break;
        }
    }
}

int MergeContactSelectListWidget::selectedContact() const
{
    return mSelectListWidget->currentRow();
}

MergeContacts::ConflictInformation MergeContactSelectListWidget::conflictType() const
{
    return mConflictType;
}

bool MergeContactSelectListWidget::verifySelectedInfo() const
{
    return selectedContact() != -1;
}

#include "moc_mergecontactselectlistwidget.cpp"
