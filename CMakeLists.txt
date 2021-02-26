cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(PIM_VERSION "5.16.40")

project(kdepim-addons VERSION ${PIM_VERSION})
if(POLICY CMP0063)
  cmake_policy(SET CMP0063 NEW)
endif()

set(KF5_MIN_VERSION "5.79.0")

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

set(QT_REQUIRED_VERSION "5.14.0")


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

set(MAILCOMMON_LIB_VERSION "5.16.40")
set(GRAVATAR_LIB_VERSION "5.16.40")
set(PIMCOMMON_LIB_VERSION "5.16.41")
set(GRANTLEETHEME_LIB_VERSION "5.16.40")
set(CALENDARSUPPORT_LIB_VERSION "5.16.40")
set(EVENTVIEW_LIB_VERSION "5.16.40")
set(LIBKDEPIM_LIB_VERSION "5.16.40")
set(KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION "5.16.40")
set(LIBKLEO_LIB_VERSION "5.16.40")
set(AKONADI_LIB_VERSION "5.16.40")
set(INCIDENCEEDITOR_LIB_VERSION "5.16.40")
set(KTNEF_LIB_VERSION "5.16.40")
set(MESSAGELIB_LIB_VERSION "5.16.49")
set(AKONADICALENDAR_LIB_VERSION "5.16.40")
set(CALENDAR_UTILS_VERSION "5.16.40")
set(KPIMTEXTEDIT_LIB_VERSION "5.16.40")
set(KIMAP_LIB_VERSION "5.16.40")
set(LIBKSIEVE_LIB_VERSION "5.16.40")
set(KMAILTRANSPORT_LIB_VERSION "5.16.40")
set(AKONADICONTACT_LIB_VERSION "5.16.40")
set(IMPORTWIZARD_LIB_VERSION "5.16.40")
set(MAILIMPORTER_LIB_VERSION "5.16.40")
set(KPIMPKPASS_LIB_VERSION "5.16.40")
set(KPIMITINERARY_LIB_VERSION "5.16.40")
set(KONTACTINTERFACE_LIB_VERSION "5.16.40")
set(AKONADINOTES_LIB_VERSION "5.16.40")
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

set(CMAKE_CXX_STANDARD 14)
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
add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x055000)

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
   if (${PC_LIBMARKDOWN_VERSION_STRING})
      if (${PC_LIBMARKDOWN_VERSION_STRING} VERSION_GREATER "2.2.5")
           set(DISCOUNT_HAS_HIGHLIGHTING_SUPPORT TRUE)
           MESSAGE(STATUS "Discount ${PC_LIBMARKDOWN_VERSION_STRING}: has hightlighting support")
      endif()
   endif()
endif()

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" FALSE)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT false)
if (USE_UNITY_CMAKE_SUPPORT)
    if(${CMAKE_VERSION} VERSION_LESS "3.16.0")
        message(STATUS "CMAKE version is less than 3.16.0 . We can't use cmake unify build support")
    else()
        set(COMPILE_WITH_UNITY_CMAKE_SUPPORT true)
    endif()
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
