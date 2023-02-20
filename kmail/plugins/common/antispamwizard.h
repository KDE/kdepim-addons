/*  -*- mode: C++ -*-
    This file is part of KMail.
    SPDX-FileCopyrightText: 2003 Andreas Gungl <a.gungl@gmx.de>

    SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <KAssistantDialog>
#include <KSharedConfig>

#include <Akonadi/Collection>
#include <QList>

class QLabel;
class QCheckBox;
class QBoxLayout;
class QListWidget;

namespace MailCommon
{
class FolderTreeWidget;
class FolderRequester;
}

namespace KMail
{
class ASWizInfoPage;
class ASWizSpamRulesPage;
class ASWizVirusRulesPage;
class ASWizSummaryPage;

//---------------------------------------------------------------------------
/**
    @short KMail anti-spam wizard.
    @author Andreas Gungl <a.gungl@gmx.de>

    The wizard helps to create filter rules to let KMail operate
    with external anti-spam tools. The wizard tries to detect the
    tools, but the user can override the preselections.
    Then the user can decide what functionality shall be supported
    by the created filter rules.
    The wizard will append the created filter rules after the
    last existing rule to keep possible conflicts with existing
    filter configurations minimal.

    Anti-virus support was added by Fred Emmott <fred87@users.sf.net>

    The configuration for the tools to get checked and set up
    is read from a config file. The structure of the file is as
    following:
    <pre>
    [General]
    tools=1

    [Spamtool #1]
    Ident=spamassassin
    Version=0
    Priority=1
    VisibleName=&Spamassassin
    Executable=spamassassin -V
    URL=http://spamassassin.org
    PipeFilterName=SpamAssassin Check
    PipeCmdDetect=spamassassin -L
    ExecCmdSpam=sa-learn --spam --no-sync --single
    ExecCmdHam=sa-learn --ham --no-sync --single
    PipeCmdNoSpam=spamassassin -d
    DetectionHeader=X-Spam-Status
    DetectionPattern=yes
    DetectionPattern2=
    DetectionOnly=0
    UseRegExp=0
    SupportsBayes=1
    SupportsUnsure=0
    ServerSided=0
    type=spam
    </pre>
    The name of the config file is kmail.antispamrc
    and it's expected in the config dir of KDE.

  */
class AntiSpamWizard : public KAssistantDialog
{
    Q_OBJECT

public:
    /** The wizard can be used for setting up anti-spam tools and for
          setting up anti-virus tools.
      */
    enum WizardMode {
        AntiSpam,
        AntiVirus,
    };

    /** Constructor that needs to initialize from the main folder tree
        of KMail.
        @param mode The mode the wizard should run in.
        @param parent The parent widget for the wizard.
        @param mainFolderTree The main folder tree from which the folders
          are copied to allow the selection of a spam folder in a tree
          within one of the wizard pages.
      */
    AntiSpamWizard(WizardMode mode, QWidget *parent);

protected:
    /**
        Instances of this class store the settings for one tool as read from
        the config file. Visible name and What's this text cannot get
        translated!
      */
    class SpamToolConfig
    {
    public:
        SpamToolConfig() = default;

        SpamToolConfig(const QString &toolId,
                       int configVersion,
                       int prio,
                       const QString &name,
                       const QString &exec,
                       const QString &url,
                       const QString &filter,
                       const QString &detection,
                       const QString &spam,
                       const QString &ham,
                       const QString &noSpam,
                       const QString &header,
                       const QString &pattern,
                       const QString &pattern2,
                       const QString &serverPattern,
                       bool detectionOnly,
                       bool regExp,
                       bool bayesFilter,
                       bool tristateDetection,
                       WizardMode type);

        Q_REQUIRED_RESULT int getVersion() const;
        Q_REQUIRED_RESULT int getPrio() const;
        Q_REQUIRED_RESULT QString getId() const;
        Q_REQUIRED_RESULT QString getVisibleName() const;
        Q_REQUIRED_RESULT QString getExecutable() const;
        Q_REQUIRED_RESULT QString getWhatsThisText() const;
        Q_REQUIRED_RESULT QString getFilterName() const;
        Q_REQUIRED_RESULT QString getDetectCmd() const;
        Q_REQUIRED_RESULT QString getSpamCmd() const;
        Q_REQUIRED_RESULT QString getHamCmd() const;
        Q_REQUIRED_RESULT QString getNoSpamCmd() const;
        Q_REQUIRED_RESULT QString getDetectionHeader() const;
        Q_REQUIRED_RESULT QString getDetectionPattern() const;
        Q_REQUIRED_RESULT QString getDetectionPattern2() const;
        Q_REQUIRED_RESULT QString getServerPattern() const;
        Q_REQUIRED_RESULT bool isServerBased() const;
        Q_REQUIRED_RESULT bool isDetectionOnly() const;
        Q_REQUIRED_RESULT bool isUseRegExp() const;
        Q_REQUIRED_RESULT bool useBayesFilter() const;
        Q_REQUIRED_RESULT bool hasTristateDetection() const;
        Q_REQUIRED_RESULT WizardMode getType() const;
        // convenience methods for types
        Q_REQUIRED_RESULT bool isSpamTool() const;
        Q_REQUIRED_RESULT bool isVirusTool() const;

    private:
        // used to identify configs for the same tool
        QString mId;
        // The version of the config data, used for merging and
        // detecting newer configs
        int mVersion;
        // the priority of the tool in the list presented to the user
        int mPrio;
        // the name as shown by the checkbox in the dialog page
        QString mVisibleName;
        // the command to check the existence of the tool
        QString mExecutable;
        // the What's This help text (e.g. url for the tool)
        QString mWhatsThisText;
        // name for the created filter in the filter list
        QString mFilterName;
        // pipe through cmd used to detect spam messages
        QString mDetectCmd;
        // pipe through cmd to let the tool learn a spam message
        QString mSpamCmd;
        // pipe through cmd to let the tool learn a ham message
        QString mHamCmd;
        // pipe through cmd to let the tool delete the spam markup
        QString mNoSpamCmd;
        // by which header are messages marked as spam
        QString mDetectionHeader;
        // what header pattern is used to mark spam messages
        QString mDetectionPattern;
        // what header pattern is used to mark unsure messages
        QString mDetectionPattern2;
        // what header pattern is used in the account to check for a certain server
        QString mServerPattern;
        // filter cannot search actively but relies on pattern by regExp or contain rule
        bool mDetectionOnly;
        // filter searches for the pattern by regExp or contain rule
        bool mUseRegExp;
        // can the tool learn spam and ham, has it a bayesian algorithm
        bool mSupportsBayesFilter;
        // differentiate between ham, spam and a third "unsure" state
        bool mSupportsUnsure;
        // Is the tool AntiSpam or AntiVirus
        WizardMode mType;
    };

    /**
        Instances of this class control reading the configuration of the
        anti-spam tools from global and user config files as well as the
        merging of different config versions.
      */
    class ConfigReader
    {
    public:
        ConfigReader(WizardMode mode, QVector<SpamToolConfig> &configList);
        ~ConfigReader();

        QVector<SpamToolConfig> &getToolList()
        {
            return mToolList;
        }

        void readAndMergeConfig();

    private:
        QVector<SpamToolConfig> &mToolList;
        KSharedConfig::Ptr mConfig;
        WizardMode mMode;

        SpamToolConfig readToolConfig(KConfigGroup &configGroup);
        SpamToolConfig createDummyConfig();

        void mergeToolConfig(const SpamToolConfig &config);
        void sortToolList();
    };

    /** Evaluate the settings made and create the appropriate filter rules. */
    void accept() override;

protected Q_SLOTS:
    /** Modify the status of the wizard to reflect the selection of spam tools. */
    void checkProgramsSelections();
    /** Modify the status of the wizard to reflect the selected functionality. */
    void checkVirusRulesSelections();
    /** Check if the spam tools are available via the PATH */
    void checkToolAvailability();
    /** Show a help topic */
    void slotHelpClicked();
    /** Create the summary text based on the current settings */
    void slotBuildSummary();

private:
    /* Check for the availability of an executible along the PATH */
    Q_REQUIRED_RESULT int checkForProgram(const QString &executable) const;
    /* generic checks if any option in a page is checked */
    Q_REQUIRED_RESULT bool anyVirusOptionChecked() const;
    /* convenience method calling the appropriate filter manager method */
    const QString uniqueNameFor(const QString &name);
    /* convenience method to sort out new and existing filters */
    void sortFilterOnExistance(const QString &intendedFilterName, QString &newFilters, QString &replaceFilters);

    /* The pages in the wizard */
    ASWizInfoPage *mInfoPage = nullptr;
    ASWizSpamRulesPage *mSpamRulesPage = nullptr;
    ASWizVirusRulesPage *mVirusRulesPage = nullptr;
    ASWizSummaryPage *mSummaryPage = nullptr;

    KPageWidgetItem *mInfoPageItem = nullptr;
    KPageWidgetItem *mSpamRulesPageItem = nullptr;
    KPageWidgetItem *mVirusRulesPageItem = nullptr;
    KPageWidgetItem *mSummaryPageItem = nullptr;

    /* The configured tools and it's settings to be used in the wizard. */
    QVector<SpamToolConfig> mToolList;

    /* Are any spam tools selected? */
    bool mSpamToolsUsed;
    /* Are any virus tools selected? */
    bool mVirusToolsUsed;

    WizardMode mMode;
};

//---------------------------------------------------------------------------
class ASWizPage : public QWidget
{
    Q_OBJECT
public:
    ASWizPage(QWidget *parent, const QString &name);

protected:
    QBoxLayout *mLayout = nullptr;
};

//---------------------------------------------------------------------------
class ASWizInfoPage : public ASWizPage
{
    Q_OBJECT

public:
    ASWizInfoPage(AntiSpamWizard::WizardMode mode, QWidget *parent, const QString &name);

    void setScanProgressText(const QString &toolName);
    void addAvailableTool(const QString &visibleName);
    Q_REQUIRED_RESULT bool isProgramSelected(const QString &visibleName) const;

Q_SIGNALS:
    void selectionChanged();

private:
    void processSelectionChange();
    QLabel *mScanProgressText = nullptr;
    QLabel *mSelectionHint = nullptr;
    QListWidget *mToolsList = nullptr;
};

//---------------------------------------------------------------------------
class ASWizSpamRulesPage : public ASWizPage
{
    Q_OBJECT

public:
    ASWizSpamRulesPage(QWidget *parent, const QString &name);

    Q_REQUIRED_RESULT bool markAsReadSelected() const;
    Q_REQUIRED_RESULT bool moveSpamSelected() const;
    Q_REQUIRED_RESULT bool moveUnsureSelected() const;

    Q_REQUIRED_RESULT QString selectedUnsureCollectionName() const;
    Q_REQUIRED_RESULT QString selectedUnsureCollectionId() const;

    void allowUnsureFolderSelection(bool enabled);
    void allowMoveSpam(bool enabled);

    Q_REQUIRED_RESULT QString selectedSpamCollectionId() const;
    Q_REQUIRED_RESULT QString selectedSpamCollectionName() const;

protected:
    Akonadi::Collection selectedSpamCollection() const;
    Akonadi::Collection selectedUnsureCollection() const;

Q_SIGNALS:
    void selectionChanged();

private:
    void processSelectionChange();
    QCheckBox *mMarkRules = nullptr;
    QCheckBox *mMoveSpamRules = nullptr;
    QCheckBox *mMoveUnsureRules = nullptr;
    MailCommon::FolderRequester *mFolderReqForSpamFolder = nullptr;
    MailCommon::FolderRequester *mFolderReqForUnsureFolder = nullptr;
};

//-------------------------------------------------------------------------
class ASWizVirusRulesPage : public ASWizPage
{
    Q_OBJECT

public:
    ASWizVirusRulesPage(QWidget *parent, const QString &name);

    Q_REQUIRED_RESULT bool pipeRulesSelected() const;
    Q_REQUIRED_RESULT bool moveRulesSelected() const;
    Q_REQUIRED_RESULT bool markReadRulesSelected() const;

    Q_REQUIRED_RESULT QString selectedFolderName() const;

Q_SIGNALS:
    void selectionChanged();

private:
    void processSelectionChange();
    QCheckBox *mPipeRules = nullptr;
    QCheckBox *mMoveRules = nullptr;
    MailCommon::FolderTreeWidget *mFolderTree = nullptr;
    QCheckBox *mMarkRules = nullptr;
};

//---------------------------------------------------------------------------
class ASWizSummaryPage : public ASWizPage
{
    Q_OBJECT

public:
    ASWizSummaryPage(QWidget *parent, const QString &name);

    void setSummaryText(const QString &text);

private:
    QLabel *const mSummaryText;
};
} // namespace KMail
