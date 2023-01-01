/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockshowlistdialog.h"
#include "adblockinterceptor_debug.h"
#include <KPIMTextEdit/PlainTextEditor>
#include <KPIMTextEdit/PlainTextEditorWidget>
#include <Libkdepim/ProgressIndicatorLabel>

#include <KConfigGroup>
#include <KIO/Job>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/SyntaxHighlighter>
#include <KSyntaxHighlighting/Theme>

#include <QDialogButtonBox>
#include <QPushButton>
#include <QTemporaryFile>
#include <QUrl>
#include <QVBoxLayout>

namespace
{
static const char myConfigAdBlockShowListDialog[] = "AdBlockShowListDialog";
}

using namespace AdBlock;
AdBlockShowListDialog::AdBlockShowListDialog(bool showDeleteBrokenList, QWidget *parent)
    : QDialog(parent)
    , mTemporaryFile(nullptr)
    , mUser1Button(nullptr)
{
    setWindowTitle(i18nc("@title:window", "Show adblock list"));
    auto mainLayout = new QVBoxLayout(this);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdBlockShowListDialog::reject);
    if (showDeleteBrokenList) {
        mUser1Button = new QPushButton(this);
        buttonBox->addButton(mUser1Button, QDialogButtonBox::ActionRole);
        mUser1Button->setText(i18n("Delete List"));
        mUser1Button->setEnabled(false);
        mUser1Button->hide();
        connect(mUser1Button, &QPushButton::clicked, this, &AdBlockShowListDialog::slotDeleteBrokenList);
    }
    auto lay = new QVBoxLayout;
    mainLayout->addLayout(lay);

    mTextEdit = new KPIMTextEdit::PlainTextEditorWidget;

    auto highlighter = new KSyntaxHighlighting::SyntaxHighlighter(mTextEdit->editor()->document());
    highlighter->setDefinition(mSyntaxRepo.definitionForName(QStringLiteral("Adblock Plus")));
    highlighter->setTheme((palette().color(QPalette::Base).lightness() < 128) ? mSyntaxRepo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                                                              : mSyntaxRepo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    mTextEdit->setReadOnly(true);
    lay->addWidget(mTextEdit);

    mProgress = new KPIM::ProgressIndicatorLabel(i18n("Download..."));
    lay->addWidget(mProgress);

    mainLayout->addWidget(buttonBox);
    readConfig();
}

AdBlockShowListDialog::~AdBlockShowListDialog()
{
    delete mTemporaryFile;
    writeConfig();
}

void AdBlockShowListDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigAdBlockShowListDialog);
    group.writeEntry("Size", size());
}

void AdBlockShowListDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigAdBlockShowListDialog);
    const QSize sizeDialog = group.readEntry("Size", QSize(800, 600));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void AdBlockShowListDialog::setAdBlockListPath(const QString &localPath, const QString &url)
{
    if (localPath.isEmpty()) {
        downLoadList(url);
    } else {
        QFile file(localPath);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            mTextEdit->editor()->setPlainText(QString::fromUtf8(file.readAll()));
        } else {
            downLoadList(url);
        }
    }
}

void AdBlockShowListDialog::downLoadList(const QString &url)
{
    delete mTemporaryFile;
    mTemporaryFile = new QTemporaryFile;
    if (!mTemporaryFile->open()) {
        qCDebug(ADBLOCKINTERCEPTOR_LOG) << "can not open temporary file";
        delete mTemporaryFile;
        mTemporaryFile = nullptr;
        return;
    }
    QUrl subUrl(url);

    QUrl destUrl = QUrl::fromLocalFile(mTemporaryFile->fileName());

    mProgress->start();
    KIO::FileCopyJob *job = KIO::file_copy(subUrl, destUrl, -1, KIO::HideProgressInfo | KIO::Overwrite);
    KIO::MetaData metadata = job->metaData();
    metadata.insert(QStringLiteral("ssl_no_client_cert"), QStringLiteral("TRUE"));
    metadata.insert(QStringLiteral("ssl_no_ui"), QStringLiteral("TRUE"));
    metadata.insert(QStringLiteral("UseCache"), QStringLiteral("false"));
    metadata.insert(QStringLiteral("cookies"), QStringLiteral("none"));
    metadata.insert(QStringLiteral("no-auth"), QStringLiteral("true"));
    job->setMetaData(metadata);

    connect(job, &KIO::FileCopyJob::finished, this, &AdBlockShowListDialog::slotFinished);
}

void AdBlockShowListDialog::slotFinished(KJob *job)
{
    mProgress->stop();
    if (job->error()) {
        mTextEdit->editor()->setPlainText(i18n("An error occurred while downloading the list: \"%1\"", job->errorString()));
        if (mUser1Button) {
            mUser1Button->show();
            mUser1Button->setEnabled(true);
        }
    } else {
        QFile f(mTemporaryFile->fileName());
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            mTextEdit->editor()->setPlainText(QString::fromUtf8(f.readAll()));
        }
    }
    mTemporaryFile->close();
    delete mTemporaryFile;
    mTemporaryFile = nullptr;
}

void AdBlockShowListDialog::slotDeleteBrokenList()
{
    Q_EMIT deleteList(mListName);
    accept();
}

void AdBlockShowListDialog::setListName(const QString &listName)
{
    mListName = listName;
}
