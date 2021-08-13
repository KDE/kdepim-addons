cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.18.1")

project(kdepim-addons VERSION ${PIM_VERSION})

set(KF5_MIN_VERSION "5.83.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/ ${ECM_MODULE_PATH})

# Do NOT add quote
set(KDEPIM_DEV_VERSION )

# add an extra space
if(DEFINED KDEPIM_DEV_VERSION)
  set(KDEPIM_DEV_VERSION " ${KDEPIM_DEV_VERSION}")
endif()

set(KDEPIMADDONS_VERSION_NUMBER ${PIM_VERSION})
set(KDEPIMADDONS_VERSION "${KDEPIMADDONS_VERSION_NUMBER}${KDEPIM_DEV_VERSION}")

set(KDEPIMADDONS_LIB_VERSION "${KDEPIMADDONS_VERSION_NUMBER}")
set(KDEPIMADDONS_LIB_SOVERSION "5")

set(QT_REQUIRED_VERSION "5.15.0")


include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMAddTests)

include(GenerateExportHeader)
include(ECMGenerateHeaders)

include(FeatureSummary)
include(KDEGitCommitHooks)
include(CheckFunctionExists)
include(ECMGeneratePriFile)


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)

option(KDEPIM_ENTERPRISE_BUILD "Enable features specific to the enterprise branch, which are normally disabled. Also, it disables many components not needed for Kontact such as the Kolab client." FALSE)

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED WebEngine WebEngineWidgets Widgets Test)

find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5DBusAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Declarative ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5SyntaxHighlighting ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Parts ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Prison ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Holidays ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5GuiAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)

set(MAILCOMMON_LIB_VERSION "5.18.1")
set(GRAVATAR_LIB_VERSION "5.18.1")
set(PIMCOMMON_LIB_VERSION "5.18.1")
set(GRANTLEETHEME_LIB_VERSION "5.18.1")
set(CALENDARSUPPORT_LIB_VERSION "5.18.1")
set(EVENTVIEW_LIB_VERSION "5.18.1")
set(LIBKDEPIM_LIB_VERSION "5.18.1")
set(KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION "5.18.1")
set(LIBKLEO_LIB_VERSION "5.18.1")
set(AKONADI_LIB_VERSION "5.18.1")
set(INCIDENCEEDITOR_LIB_VERSION "5.18.1")
set(KTNEF_LIB_VERSION "5.18.1")
set(MESSAGELIB_LIB_VERSION "5.18.1")
set(AKONADICALENDAR_LIB_VERSION "5.18.1")
set(CALENDAR_UTILS_VERSION "5.18.1")
set(KPIMTEXTEDIT_LIB_VERSION "5.18.1")
set(KIMAP_LIB_VERSION "5.18.1")
set(LIBKSIEVE_LIB_VERSION "5.18.1")
set(KMAILTRANSPORT_LIB_VERSION "5.18.1")
set(AKONADICONTACT_LIB_VERSION "5.18.1")
set(IMPORTWIZARD_LIB_VERSION "5.18.1")
set(MAILIMPORTER_LIB_VERSION "5.18.1")
set(KPIMPKPASS_LIB_VERSION "5.18.1")
set(KPIMITINERARY_LIB_VERSION "5.18.1")
set(KONTACTINTERFACE_LIB_VERSION "5.18.1")
set(AKONADINOTES_LIB_VERSION "5.18.1")
find_package(KF5AkonadiNotes ${AKONADINOTES_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarCore ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarUtils ${CALENDAR_UTILS_VERSION} CONFIG REQUIRED)
find_package(KF5WebEngineViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5TemplateParser ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MailCommon ${MAILCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimAddressbookImportExport ${KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION} CONFIG)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkdepim ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)
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
find_package(KF5Contacts ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5ContactEditor ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimImportWizard ${IMPORTWIZARD_LIB_VERSION} CONFIG)
find_package(KF5MailImporterAkonadi ${MAILIMPORTER_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimPkPass ${KPIMPKPASS_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimItinerary ${KPIMITINERARY_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5KontactInterface ${KONTACTINTERFACE_LIB_VERSION} CONFIG REQUIRED)

set(GRANTLEE_LIB_VERSION "5.2.0")
find_package(Grantlee5 ${GRANTLEE_LIB_VERSION} CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

if(KDEPIM_ENTERPRISE_BUILD)
  set(KDEPIM_ENTERPRISE_BUILD true)
else()
  set(KDEPIM_ENTERPRISE_BUILD false)
endif()

# Extra package
find_package(Gpgmepp 1.13.1 CONFIG)
set_package_properties(Gpgmepp PROPERTIES DESCRIPTION "GpgME library" URL "https://www.gnupg.org" TYPE REQUIRED)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050e00)
add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x055400)

option(KDEPIM_RUN_AKONADI_TEST "Enable autotest based on Akonadi." TRUE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(QTCREATOR_TEMPLATE_INSTALL_DIR ${KDE_INSTALL_DATADIR}/qtcreator/templates CACHE PATH "Define qtcreator template install path (default is /usr/share/qtcreator/templates)")

find_package(Discount "2")
set_package_properties("discount" PROPERTIES
        DESCRIPTION "A library that gives you formatting functions suitable for marking down entire documents or lines of text"
        URL "https://www.pell.portland.or.us/~orc/Code/discount/"
        TYPE RECOMMENDED
        PURPOSE "Generate Markdown file.")

if(discount_FOUND)
   if (${PC_LIBMARKDOWN_VERSION})
      if (${PC_LIBMARKDOWN_VERSION} VERSION_GREATER "2.2.5")
           set(DISCOUNT_HAS_HIGHLIGHTING_SUPPORT TRUE)
           MESSAGE(STATUS "Discount ${PC_LIBMARKDOWN_VERSION}: has hightlighting support")
      endif()
   endif()
endif()

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
    add_definitions(-DCOMPILE_WITH_UNITY_CMAKE_SUPPORT)
endif()

add_subdirectory(plugins)
add_subdirectory(korganizer)
add_subdirectory(kmail)
add_subdirectory(kaddressbook)
add_subdirectory(sieveeditor)
add_subdirectory(kmailtransport)
if(KPimImportWizard_FOUND)
  add_subdirectory(akonadi-import-wizard)
endif()

ecm_qt_install_logging_categories(
    EXPORT KDEPIMADDONS
    FILE kdepim-addons.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
    )
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
