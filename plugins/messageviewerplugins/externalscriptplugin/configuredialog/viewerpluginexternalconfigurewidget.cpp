/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginexternalconfigurewidget.h"
#include "externalscriptplugin_debug.h"
#include "viewerpluginexternaleditdialog.h"
#include <KConfigGroup>
#include <KDesktopFile>
#include <KLocalizedString>
#include <KMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QListWidget>
#include <QPointer>
#include <QPushButton>
#include <QStandardPaths>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

class ViewerPluginExternalScriptItem : public QListWidgetItem
{
public:
    ViewerPluginExternalScriptItem(QListWidget *parent);

    void setScriptInfo(const ViewerPluginExternalScriptInfo &scriptInfo);
    [[nodiscard]] ViewerPluginExternalScriptInfo scriptInfo() const;

private:
    ViewerPluginExternalScriptInfo mScriptInfo;
};

ViewerPluginExternalScriptItem::ViewerPluginExternalScriptItem(QListWidget *parent)
    : QListWidgetItem(parent)
{
}

void ViewerPluginExternalScriptItem::setScriptInfo(const ViewerPluginExternalScriptInfo &scriptInfo)
{
    mScriptInfo = scriptInfo;
    setText(mScriptInfo.name());
    QString commandLine = mScriptInfo.executable();
    if (!mScriptInfo.commandLine().isEmpty()) {
        commandLine += u' ' + mScriptInfo.commandLine();
    }
    setToolTip(mScriptInfo.description() + u" (%1)"_s.arg(commandLine));
}

ViewerPluginExternalScriptInfo ViewerPluginExternalScriptItem::scriptInfo() const
{
    return mScriptInfo;
}

ViewerPluginExternalConfigureWidget::ViewerPluginExternalConfigureWidget(QWidget *parent)
    : QWidget(parent)
    , mListExternal(new QListWidget(this))
    , mAddScript(new QPushButton(i18nc("@action:button", "Add Script…"), this))
    , mRemoveScript(new QPushButton(i18nc("@action:button", "Remove Script"), this))
    , mModifyScript(new QPushButton(i18nc("@action:button", "Modify Script…"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("layout"_L1);
    mainLayout->setContentsMargins({});

    auto lab = new QLabel(i18nc("@label:textbox", "External Script:"), this);
    lab->setObjectName("lab"_L1);
    mainLayout->addWidget(lab);

    auto listLayout = new QHBoxLayout;
    mainLayout->addLayout(listLayout);

    mListExternal->setObjectName("listexternal"_L1);
    mListExternal->setSelectionMode(QAbstractItemView::SingleSelection);
    mListExternal->setAlternatingRowColors(true);
    listLayout->addWidget(mListExternal);
    connect(mListExternal, &QListWidget::itemSelectionChanged, this, &ViewerPluginExternalConfigureWidget::updateButtons);
    connect(mListExternal, &QListWidget::itemDoubleClicked, this, &ViewerPluginExternalConfigureWidget::slotDoubleClicked);

    auto buttonLayout = new QVBoxLayout;
    listLayout->addLayout(buttonLayout);

    connect(mAddScript, &QPushButton::clicked, this, &ViewerPluginExternalConfigureWidget::slotAddScript);
    mAddScript->setObjectName("addscript"_L1);
    buttonLayout->addWidget(mAddScript);

    connect(mModifyScript, &QPushButton::clicked, this, &ViewerPluginExternalConfigureWidget::slotModifyScript);
    mModifyScript->setObjectName("modifyscript"_L1);
    buttonLayout->addWidget(mModifyScript);

    connect(mRemoveScript, &QPushButton::clicked, this, &ViewerPluginExternalConfigureWidget::slotRemoveScript);
    mRemoveScript->setObjectName("removescript"_L1);
    buttonLayout->addWidget(mRemoveScript);
    buttonLayout->addStretch(1);
    updateButtons();
}

ViewerPluginExternalConfigureWidget::~ViewerPluginExternalConfigureWidget() = default;

void ViewerPluginExternalConfigureWidget::slotRemoveScript()
{
    QListWidgetItem *item = mListExternal->currentItem();
    if (item) {
        const int answer = KMessageBox::warningTwoActions(this,
                                                          i18n("Do you want to remove this script \"%1\"?", item->text()),
                                                          i18nc("@title:window", "Remove External Script"),
                                                          KStandardGuiItem::remove(),
                                                          KStandardGuiItem::cancel());
        if (answer == KMessageBox::ButtonCode::PrimaryAction) {
            auto scriptItem = static_cast<ViewerPluginExternalScriptItem *>(item);
            mFilesToRemove.append(scriptItem->scriptInfo().fileName());
            delete mListExternal->takeItem(mListExternal->currentRow());
        }
    }
}

void ViewerPluginExternalConfigureWidget::slotModifyScript()
{
    QListWidgetItem *item = mListExternal->currentItem();
    if (item) {
        modifyScript(item);
    }
}

void ViewerPluginExternalConfigureWidget::slotAddScript()
{
    QStringList existingNames;
    const int numberOfElement(mListExternal->count());
    for (int i = 0; i < numberOfElement; ++i) {
        auto item = static_cast<ViewerPluginExternalScriptItem *>(mListExternal->item(i));
        existingNames << item->text();
    }
    QPointer<ViewerPluginExternalEditDialog> dlg = new ViewerPluginExternalEditDialog(this);
    dlg->setExistingsNames(existingNames);
    if (dlg->exec()) {
        auto item = new ViewerPluginExternalScriptItem(mListExternal);
        item->setScriptInfo(dlg->scriptInfo());
    }
    delete dlg;
}

void ViewerPluginExternalConfigureWidget::load()
{
    ViewerPluginExternalScriptsLoadJob job;
    const QStringList lst = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, u"messageviewerplugins/"_s, QStandardPaths::LocateDirectory);
    job.setExternalScriptsDirectories(lst);
    job.start();
    const QList<ViewerPluginExternalScriptInfo> scriptInfos = job.scriptInfos();
    fillScriptInfo(scriptInfos);
}

void ViewerPluginExternalConfigureWidget::fillScriptInfo(const QList<ViewerPluginExternalScriptInfo> &scriptInfos)
{
    for (const ViewerPluginExternalScriptInfo &script : scriptInfos) {
        auto item = new ViewerPluginExternalScriptItem(mListExternal);
        item->setScriptInfo(script);
    }
}

void ViewerPluginExternalConfigureWidget::save()
{
    for (const QString &path : std::as_const(mFilesToRemove)) {
        QFile f(path);
        if (!f.remove()) {
            qCWarning(EXTERNALSCRIPTPLUGIN_LOG) << " Impossible to delete " << path;
        }
    }
    const QString writablePath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + u"/messageviewerplugins/"_s;
    const int numberOfElement(mListExternal->count());
    for (int i = 0; i < numberOfElement; ++i) {
        auto item = static_cast<ViewerPluginExternalScriptItem *>(mListExternal->item(i));
        const ViewerPluginExternalScriptInfo &scriptInfo = item->scriptInfo();
        QString filenamepath = scriptInfo.fileName();
        if (filenamepath.isEmpty()) {
            filenamepath = writablePath + u"%1.desktop"_s.arg(scriptInfo.name());
            int fileIndex = 1;
            while (QFileInfo::exists(filenamepath)) {
                filenamepath = writablePath + u"%1-%2.desktop"_s.arg(scriptInfo.name()).arg(fileIndex);
                fileIndex++;
            }
        }
        KDesktopFile desktopFile(filenamepath);
        desktopFile.desktopGroup().writeEntry(u"Name"_s, scriptInfo.name());
        desktopFile.desktopGroup().writeEntry(u"Description"_s, scriptInfo.description());
        desktopFile.desktopGroup().writeEntry(u"Executable"_s, scriptInfo.executable());
        desktopFile.desktopGroup().writeEntry(u"CommandLine"_s, scriptInfo.commandLine());
        desktopFile.desktopGroup().writeEntry(u"Icon"_s, scriptInfo.icon());
        desktopFile.desktopGroup().sync();
    }
}

void ViewerPluginExternalConfigureWidget::updateButtons()
{
    QListWidgetItem *item = mListExternal->currentItem();
    if (item) {
        auto scriptItem = static_cast<ViewerPluginExternalScriptItem *>(item);
        const bool isReadOnly = scriptItem->scriptInfo().isReadOnly();
        mRemoveScript->setEnabled(!isReadOnly);
        mModifyScript->setEnabled(!isReadOnly);
    } else {
        mRemoveScript->setEnabled(false);
        mModifyScript->setEnabled(false);
    }
}

void ViewerPluginExternalConfigureWidget::slotDoubleClicked(QListWidgetItem *item)
{
    if (item) {
        modifyScript(item);
    }
}

void ViewerPluginExternalConfigureWidget::modifyScript(QListWidgetItem *item)
{
    auto scriptItem = static_cast<ViewerPluginExternalScriptItem *>(item);
    if (!scriptItem->scriptInfo().isReadOnly()) {
        QPointer<ViewerPluginExternalEditDialog> dlg = new ViewerPluginExternalEditDialog(this);
        dlg->setScriptInfo(scriptItem->scriptInfo());
        if (dlg->exec()) {
            scriptItem->setScriptInfo(dlg->scriptInfo());
        }
        delete dlg;
    }
}

#include "moc_viewerpluginexternalconfigurewidget.cpp"
