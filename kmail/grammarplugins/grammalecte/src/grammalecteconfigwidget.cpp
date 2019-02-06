/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "grammalecteconfigwidget.h"
#include "grammalectemanager.h"

#include <KMessageBox>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>

#include <QVBoxLayout>
#include <QTabWidget>
#include <QCheckBox>
#include <QScrollArea>
#include <QFormLayout>

#include <KUrlRequester>

GrammalecteConfigWidget::GrammalecteConfigWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    QTabWidget *mTab = new QTabWidget(this);
    mTab->setObjectName(QStringLiteral("mTab"));
    mainLayout->addWidget(mTab);
    mTab->addTab(addGeneralTab(), i18n("General"));
    mTab->addTab(addGrammarTab(), i18n("Grammar Settings"));
    loadSettings(); //First
    loadGrammarSettings();
}

GrammalecteConfigWidget::~GrammalecteConfigWidget()
{
    saveSettings();
}

void GrammalecteConfigWidget::loadGrammarSettings()
{
    GrammalecteGenerateConfigOptionJob *job = new GrammalecteGenerateConfigOptionJob(this);
    job->setPythonPath(GrammalecteManager::self()->pythonPath());
    job->setGrammarlecteCliPath(GrammalecteManager::self()->grammalectePath());
    connect(job, &GrammalecteGenerateConfigOptionJob::finished, this, &GrammalecteConfigWidget::slotGetSettingsFinished);
    connect(job, &GrammalecteGenerateConfigOptionJob::error, this, &GrammalecteConfigWidget::slotGetSettingsError);
    job->start();
}

void GrammalecteConfigWidget::slotGetSettingsError()
{
    KMessageBox::error(this, i18n("Error during Extracting Options"), i18n("Impossible to get options. Please verify that you have grammalected installed."));
}

void GrammalecteConfigWidget::slotGetSettingsFinished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result)
{
    mListOptions.reserve(result.count());
    for (const GrammalecteGenerateConfigOptionJob::Option &opt : result) {
        QCheckBox *box = new QCheckBox(opt.description, this);
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
    QScrollArea *area = new QScrollArea(this);
    area->setWidgetResizable(true);
    mGrammarTabWidget = new QWidget;
    mGrammarTabWidget->setObjectName(QStringLiteral("grammar"));
    QVBoxLayout *layout = new QVBoxLayout(mGrammarTabWidget);
    layout->setObjectName(QStringLiteral("grammartablayout"));
    area->setWidget(mGrammarTabWidget);
    return area;
}

QWidget *GrammalecteConfigWidget::addGeneralTab()
{
    QWidget *w = new QWidget(this);
    w->setObjectName(QStringLiteral("general"));
    QFormLayout *lay = new QFormLayout(w);
    lay->setMargin(0);
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
    KConfigGroup grp(KSharedConfig::openConfig(), "Grammalecte");
    mPythonPath->setText(grp.readEntry(QStringLiteral("pythonpath")));
    mGrammalectePath->setText(grp.readEntry(QStringLiteral("grammalectepath")));
    mSaveOptions = grp.readEntry(QStringLiteral("options"), QStringList());
}

void GrammalecteConfigWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Grammalecte");
    grp.writeEntry(QStringLiteral("pythonpath"), mPythonPath->text());
    grp.writeEntry(QStringLiteral("grammalectepath"), mGrammalectePath->text());
    QStringList result;
    for (QCheckBox *checkBox : qAsConst(mListOptions)) {
        if (checkBox->isChecked()) {
            result += checkBox->property("optionname").toString();
        }
    }
    grp.writeEntry(QStringLiteral("options"), result);
}
