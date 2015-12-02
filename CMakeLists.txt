project(kdepim-addons)

cmake_minimum_required(VERSION 2.8.12)
find_package(ECM 5.16.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

# Do NOT add quote
set(KDEPIMADDONS_DEV_VERSION pre)

# add an extra space
if(DEFINED KDEPIMADDONS_DEV_VERSION)
  set(KDEPIMADDONS_DEV_VERSION " ${KDEPIMADDONS_DEV_VERSION}")
endif()

set(KDEPIMADDONS_VERSION_NUMBER "5.1.40")
set(KDEPIMADDONS_VERSION "${KDEPIMADDONS_VERSION_NUMBER}${KDEPIMADDONS_DEV_VERSION}")

set(KDEPIMADDONS_LIB_VERSION "${KDEPIMADDONS_VERSION_NUMBER}")
set(KDEPIMADDONS_LIB_SOVERSION "5")

set(AKONADINOTES_LIB_VERSION "4.78.0")
set(QT_REQUIRED_VERSION "5.4.0")
set(KF5_VERSION "5.16.0")
include(ECMOptionalAddSubdirectory)
include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMAddTests)
include(ECMMarkNonGuiExecutable)
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(FeatureSummary)
include(CheckFunctionExists)
include(ECMGeneratePriFile)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)

option(KDEPIMADDONS_BUILD_EXAMPLES "Build the kdepim-addons example applications." TRUE)



find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)
find_package(Qt5X11Extras NO_MODULE)
find_package(Qt5Designer NO_MODULE)
set_package_properties(Qt5Designer PROPERTIES
   PURPOSE "Required to build the Qt Designer plugins"
   TYPE OPTIONAL
)

find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KHtml ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5DBusAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiNotes ${AKONADINOTES_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_VERSION} CONFIG REQUIRED)

set(KDEPIM_LIB_INSTALLED_VERSION "5.1.41")

set(MAILCOMMN_LIB_VERSION "5.1.41")
set(GRAVATAR_LIB_VERSION "5.1.41")
set(PIMCOMMON_LIB_VERSION "5.1.41")
set(KDGANTT2_LIB_VERSION "5.1.41")

find_package(KF5MailCommon ${MAILCOMMN_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5KaddressbookGrantlee ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5MessageViewer ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommon ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5IncidenceEditorsng ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5MessageCore ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5MessageComposer ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5MessageList ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5TemplateParser ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5MailImporter ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarSupport ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5EventViews ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5KDGantt2 ${KDGANTT2_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5FollowupReminder ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5SendLater ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5ComposerEditorNG ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5KdepimDBusInterfaces ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5LibKSieve ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5Gravatar ${GRAVATAR_LIB_VERSION} CONFIG REQUIRED)
find_package(MailTransportDBusService CONFIG REQUIRED)

add_definitions( -DQT_NO_CAST_FROM_ASCII )
add_definitions( -DQT_NO_CAST_TO_ASCII )


if (KDEPIMADDONS_BUILD_EXAMPLES)
   add_subdirectory(examples)
endif()

add_subdirectory(plugins)
add_subdirectory(korganizer)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
