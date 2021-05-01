/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigwidget.h"
#include "grammalectemanager.h"

#include <KLocalizedString>
#include <KMessageBox>

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTabWidget>
#include <QToolButton>
#include <QVBoxLayout>

#include <KUrlRequester>
GrammalecteConfigWidget::GrammalecteConfigWidget(QWidget *parent, bool disableMessageBox)
    : QWidget(parent)
    , mDisableDialogBox(disableMessageBox)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    auto mTab = new QTabWidget(this);
    mTab->setObjectName(QStringLiteral("mTab"));
    mainLayout->addWidget(mTab);
    mTab->addTab(addGeneralTab(), i18n("General"));
    mTab->addTab(addGrammarTab(), i18n("Grammar Settings"));
    loadSettings(); // First
    loadGrammarSettings();
}

GrammalecteConfigWidget::~GrammalecteConfigWidget()
{
    saveSettings();
}

void GrammalecteConfigWidget::loadGrammarSettings()
{
    auto job = new GrammalecteGenerateConfigOptionJob(this);
    job->setPythonPath(mPythonPath->text());
    job->setGrammarlecteCliPath(mGrammalectePath->text());
    connect(job, &GrammalecteGenerateConfigOptionJob::finished, this, &GrammalecteConfigWidget::slotGetSettingsFinished);
    connect(job, &GrammalecteGenerateConfigOptionJob::error, this, &GrammalecteConfigWidget::slotGetSettingsError);
    job->start();
}

void GrammalecteConfigWidget::slotGetSettingsError()
{
    mStackedWidget->setCurrentWidget(mReloadSettingsWidget);
    if (!mDisableDialogBox) {
        KMessageBox::error(this,
                           i18n("Impossible to get options. Please verify that you have grammalected installed."),
                           i18n("Error during Extracting Options"));
    }
}

void GrammalecteConfigWidget::slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result)
{
    mStackedWidget->setCurrentWidget(mScrollArea);
    mListOptions.clear();
    mListOptions.reserve(result.count());
    delete mGrammarTabWidget->layout();
    auto layout = new QVBoxLayout(mGrammarTabWidget);
    layout->setObjectName(QStringLiteral("grammartablayout"));

    for (const GrammalecteGenerateConfigOptionJob::Option &opt : result) {
        auto box = new QCheckBox(opt.description, this);
        box->setProperty("optionname", opt.optionName);
        if (mSaveOptions.isEmpty()) {
            box->setChecked(opt.defaultValue);
        } else {
            box->setChecked(mSaveOptions.contains(opt.optionName));
        }
        mGrammarTabWidget->layout()->addWidget(box);
        mListOptions.append(box);
    }
}

QWidget *GrammalecteConfigWidget::addGrammarTab()
{
    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));

    mScrollArea = new QScrollArea(this);
    mScrollArea->setObjectName(QStringLiteral("scrollarea"));
    mScrollArea->setWidgetResizable(true);
    mGrammarTabWidget = new QWidget;
    mGrammarTabWidget->setObjectName(QStringLiteral("grammar"));
    auto layout = new QVBoxLayout(mGrammarTabWidget);
    layout->setObjectName(QStringLiteral("grammartablayout"));
    mScrollArea->setWidget(mGrammarTabWidget);

    mStackedWidget->addWidget(mScrollArea);

    mReloadSettingsWidget = new QWidget;
    mReloadSettingsWidget->setObjectName(QStringLiteral("reloadwidget"));
    mStackedWidget->addWidget(mReloadSettingsWidget);
    auto reloadSettingsLayout = new QVBoxLayout(mReloadSettingsWidget);
    reloadSettingsLayout->setObjectName(QStringLiteral("reloadSettingsLayout"));
    auto horizontallayout = new QHBoxLayout;
    reloadSettingsLayout->addLayout(horizontallayout);
    auto label = new QLabel(i18n("Press Button for Reloading Settings"), this);
    label->setObjectName(QStringLiteral("label"));
    horizontallayout->addWidget(label);

    auto buttonReloadSettings = new QToolButton(this);
    buttonReloadSettings->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
    buttonReloadSettings->setObjectName(QStringLiteral("buttonReloadSettings"));
    buttonReloadSettings->setToolTip(i18n("Reload Settings"));
    horizontallayout->addWidget(buttonReloadSettings);
    connect(buttonReloadSettings, &QToolButton::clicked, this, &GrammalecteConfigWidget::loadGrammarSettings);

    reloadSettingsLayout->addStretch(1);
    return mStackedWidget;
}

QWidget *GrammalecteConfigWidget::addGeneralTab()
{
    auto w = new QWidget(this);
    w->setObjectName(QStringLiteral("general"));
    auto lay = new QFormLayout(w);
    lay->setObjectName(QStringLiteral("generallayout"));

    mPythonPath = new KUrlRequester(this);
    mPythonPath->setObjectName(QStringLiteral("pythonpath"));
    lay->addRow(i18n("Python Path:"), mPythonPath);

    mGrammalectePath = new KUrlRequester(this);
    mGrammalectePath->setObjectName(QStringLiteral("grammalectepath"));
    lay->addRow(i18n("Grammalecte Path:"), mGrammalectePath);

    return w;
}

void GrammalecteConfigWidget::loadSettings()
{
    mPythonPath->setText(GrammalecteManager::self()->pythonPath());
    mGrammalectePath->setText(GrammalecteManager::self()->grammalectePath());
    mSaveOptions = GrammalecteManager::self()->options();
}

void GrammalecteConfigWidget::saveSettings()
{
    QStringList result;
    for (QCheckBox *checkBox : qAsConst(mListOptions)) {
        if (checkBox->isChecked()) {
            result += checkBox->property("optionname").toString();
        }
    }
    GrammalecteManager::self()->setPythonPath(mPythonPath->text());
    GrammalecteManager::self()->setGrammalectePath(mGrammalectePath->text());
    GrammalecteManager::self()->setOptions(result);
    GrammalecteManager::self()->saveSettings();
}
