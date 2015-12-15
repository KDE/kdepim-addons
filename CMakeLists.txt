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

find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KHtml ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5DBusAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiNotes ${AKONADINOTES_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_VERSION} CONFIG REQUIRED)

set(KDEPIM_LIB_INSTALLED_VERSION "5.1.42")

set(MAILCOMMN_LIB_VERSION "5.1.42")
set(GRAVATAR_LIB_VERSION "5.1.42")
set(PIMCOMMON_LIB_VERSION "5.1.42")
set(KDGANTT2_LIB_VERSION "5.1.42")
set(GRANTLEETHEME_LIB_VERSION "5.1.42")
set(CALENDARSUPPORT_LIB_VERSION "5.1.42")
set(EVENTVIEW_LIB_VERSION "5.1.42")
set(KSIEVE_LIB_VERSION "5.1.42")
set(LIBKDEPIM_LIB_VERSION "5.1.42")
set(MAILIMPORTER_LIB_VERSION "5.1.42")
set(MESSAGELIB_LIB_VERSION "5.1.42")
set(KDEPIM_APPS_LIB_VERSION "5.1.42")
set(LIBKLEO_LIB_VERSION "5.1.42")
set(KDEPIMLIBS_LIB_VERSION "5.1.42")

find_package(KF5MailCommon ${MAILCOMMN_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5KaddressbookGrantlee ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5MessageViewer ${KDEPIM_APPS_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommon ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5IncidenceEditorsng ${KDEPIM_LIB_INSTALLED_VERSION} CONFIG REQUIRED)
find_package(KF5MessageCore ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageComposer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageList ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarSupport ${CALENDARSUPPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5EventViews ${EVENTVIEW_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${KDEPIMLIBS_LIB_VERSION} CONFIG REQUIRED)
add_definitions( -DQT_NO_CAST_FROM_ASCII )
add_definitions( -DQT_NO_CAST_TO_ASCII )

# Extra package
find_package(KF5GAPI "4.72.0" CONFIG)

if (KDEPIMADDONS_BUILD_EXAMPLES)
   add_subdirectory(examples)
endif()

add_subdirectory(plugins)
add_subdirectory(korganizer)
add_subdirectory(kmail)
add_subdirectory(kaddressbook)
add_subdirectory(grantleefilters)

install( FILES kdepim-addons.categories DESTINATION ${KDE_INSTALL_CONFDIR} )
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
