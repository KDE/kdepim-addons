cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.11.40")

project(kdepim-addons VERSION ${PIM_VERSION})
if(POLICY CMP0063)
  cmake_policy(SET CMP0063 NEW)
endif()

set(KF5_MIN_VERSION "5.56.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/ ${ECM_MODULE_PATH})

# Do NOT add quote
set(KDEPIM_DEV_VERSION alpha)

# add an extra space
if(DEFINED KDEPIM_DEV_VERSION)
  set(KDEPIM_DEV_VERSION " ${KDEPIM_DEV_VERSION}")
endif()

set(KDEPIMADDONS_VERSION_NUMBER ${PIM_VERSION})
set(KDEPIMADDONS_VERSION "${KDEPIMADDONS_VERSION_NUMBER}${KDEPIM_DEV_VERSION}")

set(KDEPIMADDONS_LIB_VERSION "${KDEPIMADDONS_VERSION_NUMBER}")
set(KDEPIMADDONS_LIB_SOVERSION "5")

set(AKONADINOTES_LIB_VERSION "5.11.0")
set(QT_REQUIRED_VERSION "5.10.0")


include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMAddTests)

include(GenerateExportHeader)
include(ECMGenerateHeaders)

include(FeatureSummary)
include(CheckFunctionExists)
include(ECMGeneratePriFile)


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)

option(KDEPIMADDONS_BUILD_EXAMPLES "Build the kdepim-addons example applications." TRUE)

option(KDEPIM_ENTERPRISE_BUILD "Enable features specific to the enterprise branch, which are normally disabled. Also, it disables many components not needed for Kontact such as the Kolab client." FALSE)

option(KMAIL_EDITORCONVERTERPLUGIN_TEMPLATE_BUILD "Build the kmail editor converter plugin." FALSE)

option(KMAIL_DKIM_CONFIGURE_DIALOG_BUILD "Build dkim-verify configure dialog (experimental)." FALSE)

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED WebEngine WebEngineWidgets Widgets Test)

find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5DBusAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiNotes ${AKONADINOTES_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Declarative ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5SyntaxHighlighting ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Parts ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Prison ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Holidays ${KF5_MIN_VERSION} CONFIG REQUIRED)

set(MAILCOMMON_LIB_VERSION "5.11.0")
set(GRAVATAR_LIB_VERSION "5.11.0")
set(PIMCOMMON_LIB_VERSION "5.11.0")
set(GRANTLEETHEME_LIB_VERSION "5.11.0")
set(CALENDARSUPPORT_LIB_VERSION "5.11.0")
set(EVENTVIEW_LIB_VERSION "5.11.0")
set(LIBKDEPIM_LIB_VERSION "5.11.0")
set(KDEPIM_APPS_LIB_VERSION "5.11.0")
set(LIBKLEO_LIB_VERSION "5.11.0")
set(AKONADI_LIB_VERSION "5.11.0")
set(INCIDENCEEDITOR_LIB_VERSION "5.11.0")
set(KTNEF_LIB_VERSION "5.11.0")
set(MESSAGELIB_LIB_VERSION "5.11.0")
set(AKONADICALENDAR_LIB_VERSION "5.11.0")
set(CALENDAR_UTILS_VERSION "5.11.0")
set(KPIMTEXTEDIT_LIB_VERSION "5.11.0")
set(KIMAP_LIB_VERSION "5.11.0")
set(LIBKSIEVE_LIB_VERSION "5.11.0")
set(KMAILTRANSPORT_LIB_VERSION "5.11.0")
set(AKONADICONTACT_LIB_VERSION "5.11.0")
set(IMPORTWIZARD_LIB_VERSION "5.11.0")
set(MAILIMPORTER_LIB_VERSION "5.11.0")
set(KPIMPKPASS_LIB_VERSION "5.11.0")
set(KPIMITINERARY_LIB_VERSION "5.11.0")

find_package(KF5CalendarUtils ${CALENDAR_UTILS_VERSION} CONFIG REQUIRED)
find_package(KF5WebEngineViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5TemplateParser ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MailCommon ${MAILCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5KaddressbookGrantlee ${KDEPIM_APPS_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5KaddressbookImportExport ${KDEPIM_APPS_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5LibkdepimAkonadi ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5IncidenceEditor ${INCIDENCEEDITOR_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageCore ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageComposer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageList ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarSupport ${CALENDARSUPPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5EventViews ${EVENTVIEW_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Akonadi ${AKONADI_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiCalendar ${AKONADICALENDAR_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Gravatar ${GRAVATAR_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimTextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5IdentityManagement ${KIDENTITYMANAGEMENT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5LibKSieve ${LIBKSIEVE_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Tnef ${KTNEF_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MailTransportAkonadi ${KMAILTRANSPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimImportWizard ${IMPORTWIZARD_LIB_VERSION} CONFIG)
find_package(KF5MailImporterAkonadi ${MAILIMPORTER_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimPkPass ${KPIMPKPASS_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimItinerary ${KPIMITINERARY_LIB_VERSION} CONFIG REQUIRED)

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

if(KDEPIM_ENTERPRISE_BUILD)
  set(KDEPIM_ENTERPRISE_BUILD true)
else()
  set(KDEPIM_ENTERPRISE_BUILD false)
endif()

# Extra package
find_package(Gpgmepp 1.8.0 CONFIG)
set_package_properties(Gpgmepp PROPERTIES DESCRIPTION "GpgME library" URL "https://www.gnupg.org" TYPE REQUIRED)
# workaround for https://bugreports.qt.io/browse/QTBUG-74665 (bug in qt5.13 reevaluate it)
if (${Qt5Widgets_VERSION} STRGREATER "5.13")
   MESSAGE(STATUS "Qt version: ${Qt5Widgets_VERSION} DISABLE compile without deprecated methods. bug QTBUG-74665")
else()
   add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
endif()
if (${KF5Config_VERSION} STRGREATER "5.56.0")
        add_definitions(-DQT_NO_FOREACH)
        MESSAGE(STATUS "compile without foreach")
endif()

if(KDEPIMADDONS_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(QTCREATOR_TEMPLATE_INSTALL_DIR ${KDE_INSTALL_DATADIR}/qtcreator/templates CACHE PATH "Define qtcreator template install path (default is /usr/share/qtcreator/templates)")

find_package(Discount "2")
set_package_properties("discount" PROPERTIES
        DESCRIPTION "A library that gives you formatting functions suitable for marking down entire documents or lines of text"
        URL "https://www.pell.portland.or.us/~orc/Code/discount/"
        TYPE RECOMMENDED
        PURPOSE "Generate Markdown file.")


add_subdirectory(plugins)
add_subdirectory(korganizer)
add_subdirectory(kmail)
add_subdirectory(kaddressbook)
add_subdirectory(sieveeditor)
add_subdirectory(kmailtransport)
if(KPimImportWizard_FOUND)
  add_subdirectory(akonadi-import-wizard)
endif()

install(FILES kdepim-addons.categories kdepim-addons.renamecategories DESTINATION ${KDE_INSTALL_CONFDIR})
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
