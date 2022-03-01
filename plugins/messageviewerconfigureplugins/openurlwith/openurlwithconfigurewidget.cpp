/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidget.h"
#include "openurlwithconfigurecreatedialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <MessageViewer/OpenUrlWithManager>
#include <MessageViewer/OpenWithUrlInfo>
#include <QHeaderView>
#include <QListWidget>
#include <QMenu>
#include <QPointer>
#include <QTreeWidget>
#include <QVBoxLayout>

class OpenUrlWithConfigureItem : public QListWidgetItem
{
public:
    explicit OpenUrlWithConfigureItem(QListWidget *parent);

    void setInfo(const MessageViewer::OpenWithUrlInfo &info);
    Q_REQUIRED_RESULT MessageViewer::OpenWithUrlInfo info() const;

private:
    MessageViewer::OpenWithUrlInfo mScriptInfo;
};

OpenUrlWithConfigureItem::OpenUrlWithConfigureItem(QListWidget *parent)
    : QListWidgetItem(parent)
{
}

void OpenUrlWithConfigureItem::setInfo(const MessageViewer::OpenWithUrlInfo &scriptInfo)
{
    mScriptInfo = scriptInfo;
    setText(mScriptInfo.command());
    QString commandLine = mScriptInfo.command();
    if (!mScriptInfo.commandLine().isEmpty()) {
        commandLine += QLatin1Char(' ') + mScriptInfo.commandLine();
    }
    setToolTip(commandLine);
}

MessageViewer::OpenWithUrlInfo OpenUrlWithConfigureItem::info() const
{
    return mScriptInfo;
}

OpenUrlWithConfigureWidget::OpenUrlWithConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mListWidget(new QListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins());

    mListWidget->setObjectName(QStringLiteral("mListWidget"));
    mainLayout->addWidget(mListWidget);
    mListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mListWidget->setAlternatingRowColors(true);
    mListWidget->setSortingEnabled(true);
    connect(mListWidget, &QListWidget::customContextMenuRequested, this, &OpenUrlWithConfigureWidget::slotCustomContextMenuRequested);
    connect(mListWidget, &QListWidget::itemDoubleClicked, this, &OpenUrlWithConfigureWidget::slotEditRule);
}

OpenUrlWithConfigureWidget::~OpenUrlWithConfigureWidget()
{
}

void OpenUrlWithConfigureWidget::displayText(const MessageViewer::OpenWithUrlInfo &r, OpenUrlWithConfigureItem *item)
{
    item->setInfo(r);
    item->setText(QStringLiteral("%1 (%2)").arg(r.command() + QLatin1Char(' ') + r.commandLine(), r.url()));
}

void OpenUrlWithConfigureWidget::loadSettings()
{
    const QVector<MessageViewer::OpenWithUrlInfo> rules = MessageViewer::OpenUrlWithManager::self()->openWithUrlInfo();
    for (const MessageViewer::OpenWithUrlInfo &r : rules) {
        auto item = new OpenUrlWithConfigureItem(mListWidget);
        displayText(r, item);
    }
}

void OpenUrlWithConfigureWidget::writeSettings()
{
    QVector<MessageViewer::OpenWithUrlInfo> rules;
    for (int i = 0, total = mListWidget->count(); i < total; ++i) {
        OpenUrlWithConfigureItem *item = static_cast<OpenUrlWithConfigureItem *>(mListWidget->item(i));
        const MessageViewer::OpenWithUrlInfo r = item->info();
        rules.append(r);
    }
    MessageViewer::OpenUrlWithManager::self()->setOpenWithUrlInfo(rules);
    MessageViewer::OpenUrlWithManager::self()->saveRules();
}

void OpenUrlWithConfigureWidget::slotAddRule()
{
    QPointer<OpenUrlWithConfigureCreateDialog> dlg = new OpenUrlWithConfigureCreateDialog(this);
    if (dlg->exec()) {
        const OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo info = dlg->info();
        if (info.isValid()) {
            MessageViewer::OpenWithUrlInfo r;
            r.setCommand(info.command);
            r.setCommandLine(info.commandLines);
            r.setUrl(info.url);

            for (int i = 0, total = mListWidget->count(); i < total; ++i) {
                OpenUrlWithConfigureItem *item = static_cast<OpenUrlWithConfigureItem *>(mListWidget->item(i));
                const MessageViewer::OpenWithUrlInfo openInfo = item->info();
                if (openInfo == r) {
                    KMessageBox::information(this, i18n("Rule already exists."), i18n("Duplicate Rule"));
                    delete dlg;
                    return;
                }
            }
            auto item = new OpenUrlWithConfigureItem(mListWidget);
            displayText(r, item);
        }
    }
    delete dlg;
}

void OpenUrlWithConfigureWidget::slotEditRule()
{
    OpenUrlWithConfigureItem *item = dynamic_cast<OpenUrlWithConfigureItem *>(mListWidget->currentItem());
    if (item) {
        QPointer<OpenUrlWithConfigureCreateDialog> dlg = new OpenUrlWithConfigureCreateDialog(this);
        OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo info;
        MessageViewer::OpenWithUrlInfo r = item->info();
        info.command = r.command();
        info.url = r.url();
        info.commandLines = r.commandLine();
        dlg->setInfo(info);
        if (dlg->exec()) {
            const OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo info = dlg->info();
            if (info.isValid()) {
                r.setCommand(info.command);
                r.setCommandLine(info.commandLines);
                r.setUrl(info.url);
                displayText(r, item);
            }
        }
        delete dlg;
    }
}

void OpenUrlWithConfigureWidget::slotRemoveRule()
{
    auto items = mListWidget->selectedItems();
    if (!items.isEmpty()) {
        const int answer = KMessageBox::questionYesNo(this,
                                                      i18np("Do you want to remove this rule?", "Do you want to remove these rules?", items.count()),
                                                      i18nc("@title", "Remove Rule"),
                                                      KStandardGuiItem::remove(),
                                                      KStandardGuiItem::cancel());

        if (answer == KMessageBox::Yes) {
            while (!items.isEmpty()) {
                delete items.takeFirst();
            }
        }
    }
}

void OpenUrlWithConfigureWidget::slotCustomContextMenuRequested(const QPoint &p)
{
    QMenu menu(this);
    const int selectedItemCount{mListWidget->selectedItems().count()};
    menu.addAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add Rule..."), this, &OpenUrlWithConfigureWidget::slotAddRule);
    if (selectedItemCount == 1) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18n("Edit Rule..."), this, &OpenUrlWithConfigureWidget::slotEditRule);
    }
    if (selectedItemCount > 0) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("list-remove")),
                       i18np("Remove Rule", "Remove Rules", selectedItemCount),
                       this,
                       &OpenUrlWithConfigureWidget::slotRemoveRule);
    }
    menu.exec(QCursor::pos());
}
