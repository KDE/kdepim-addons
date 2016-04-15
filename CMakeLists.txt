project(kdepim-addons)

cmake_minimum_required(VERSION 2.8.12)
if (POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

find_package(ECM 5.20.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

# Do NOT add quote
set(KDEPIMADDONS_DEV_VERSION pre)

# add an extra space
if(DEFINED KDEPIMADDONS_DEV_VERSION)
  set(KDEPIMADDONS_DEV_VERSION " ${KDEPIMADDONS_DEV_VERSION}")
endif()

set(KDEPIMADDONS_VERSION_NUMBER "5.2.41")
set(KDEPIMADDONS_VERSION "${KDEPIMADDONS_VERSION_NUMBER}${KDEPIMADDONS_DEV_VERSION}")

set(KDEPIMADDONS_LIB_VERSION "${KDEPIMADDONS_VERSION_NUMBER}")
set(KDEPIMADDONS_LIB_SOVERSION "5")

set(AKONADINOTES_LIB_VERSION "5.2.40")
set(QT_REQUIRED_VERSION "5.6.0")
set(KF5_VERSION "5.20.0")
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
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)

option(KDEPIMADDONS_BUILD_EXAMPLES "Build the kdepim-addons example applications." TRUE)

option(QTWEBENGINE_SUPPORT_OPTION "Enable support for QtWebEngine. False by default." FALSE)

if (QTWEBENGINE_SUPPORT_OPTION)
    find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED WebEngine WebEngineWidgets)
    find_package(KF5WebEngineViewer ${KDEPIM_APPS_LIB_VERSION} CONFIG REQUIRED)
endif()


find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)

find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5DBusAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiNotes ${AKONADINOTES_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_VERSION} CONFIG REQUIRED)

set(MAILCOMMN_LIB_VERSION "5.2.40")
set(GRAVATAR_LIB_VERSION "5.2.40")
set(PIMCOMMON_LIB_VERSION "5.2.40")
set(KDGANTT2_LIB_VERSION "5.2.40")
set(GRANTLEETHEME_LIB_VERSION "5.2.40")
set(CALENDARSUPPORT_LIB_VERSION "5.2.40")
set(EVENTVIEW_LIB_VERSION "5.2.40")
set(KSIEVE_LIB_VERSION "5.2.40")
set(LIBKDEPIM_LIB_VERSION "5.2.40")
set(MAILIMPORTER_LIB_VERSION "5.2.40")
set(KDEPIM_APPS_LIB_VERSION "5.2.40")
set(LIBKLEO_LIB_VERSION "5.2.40")
set(KDEPIMLIBS_LIB_VERSION "5.2.40")
set(GRAVATAR_LIB_VERSION "5.2.40")
set(INCIDENCEEDITOR_LIB_VERSION "5.2.40")
set(KTNEF_LIB_VERSION "5.2.40")
set(MESSAGELIB_LIB_VERSION "5.2.56")

find_package(KF5MailCommon ${MAILCOMMN_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5KaddressbookGrantlee ${KDEPIM_APPS_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageViewer ${KDEPIM_APPS_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommon ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5IncidenceEditor ${INCIDENCEEDITOR_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageCore ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageComposer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageList ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarSupport ${CALENDARSUPPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5EventViews ${EVENTVIEW_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5Gravatar ${GRAVATAR_LIB_VERSION} CONFIG REQUIRED)

find_package(KF5Tnef ${KTNEF_LIB_VERSION} CONFIG REQUIRED)

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
add_subdirectory(akregator)

install( FILES kdepim-addons.categories DESTINATION ${KDE_INSTALL_CONFDIR} )
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
