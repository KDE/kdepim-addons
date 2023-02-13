# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.22.40")

project(kdepim-addons VERSION ${PIM_VERSION})

set(KF_MIN_VERSION "5.103.0")

find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
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

set(QT_REQUIRED_VERSION "5.15.2")


include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMAddTests)

include(GenerateExportHeader)
include(ECMGenerateHeaders)

include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})
include(CheckFunctionExists)
include(ECMGeneratePriFile)


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_REQUIRED_VERSION "6.4.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
    set(KTEXTADDONS_MIN_VERSION "1.1.0")
else()
    set(KF_MAJOR_VERSION "5")
    set(KTEXTADDONS_MIN_VERSION "1.0.0")
endif()

option(KDEPIM_ENTERPRISE_BUILD "Enable features specific to the enterprise branch, which are normally disabled. Also, it disables many components not needed for Kontact such as the Kolab client." FALSE)


find_package(Qt${QT_MAJOR_VERSION} ${QT_REQUIRED_VERSION} CONFIG REQUIRED WebEngineWidgets Widgets Test)

if (QT_MAJOR_VERSION STREQUAL "6")
    find_package(Qt6Core5Compat)
endif()

find_package(KF${KF_MAJOR_VERSION}I18n ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Config ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}DBusAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}XmlGui ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Declarative ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}SyntaxHighlighting ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}KIO ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}IconThemes ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Parts ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Prison ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}Holidays ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}GuiAddons ${KF_MIN_VERSION} CONFIG REQUIRED)

set(MAILCOMMON_LIB_VERSION "5.22.40")
set(GRAVATAR_LIB_VERSION "5.22.40")
set(PIMCOMMON_LIB_VERSION "5.22.47")
set(GRANTLEETHEME_LIB_VERSION "5.22.40")
set(CALENDARSUPPORT_LIB_VERSION "5.22.40")
set(EVENTVIEW_LIB_VERSION "5.22.40")
set(LIBKDEPIM_LIB_VERSION "5.22.40")
set(KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION "5.22.40")
set(LIBKLEO_LIB_VERSION "5.22.40")
set(AKONADI_LIB_VERSION "5.22.40")
set(INCIDENCEEDITOR_LIB_VERSION "5.22.40")
set(KTNEF_LIB_VERSION "5.22.40")
set(MESSAGELIB_LIB_VERSION "5.22.40")
set(AKONADICALENDAR_LIB_VERSION "5.22.40")
set(CALENDAR_UTILS_VERSION "5.22.40")
set(KPIMTEXTEDIT_LIB_VERSION "5.22.40")
set(KIMAP_LIB_VERSION "5.22.40")
set(LIBKSIEVE_LIB_VERSION "5.22.40")
set(KMAILTRANSPORT_LIB_VERSION "5.22.40")
set(AKONADICONTACT_LIB_VERSION "5.22.40")
set(IMPORTWIZARD_LIB_VERSION "5.22.40")
set(MAILIMPORTER_LIB_VERSION "5.22.40")
set(KPIMPKPASS_LIB_VERSION "5.22.40")
set(KPIMITINERARY_LIB_VERSION "5.22.40")
set(AKONADINOTES_LIB_VERSION "5.22.40")
find_package(KF5AkonadiNotes ${AKONADINOTES_LIB_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}CalendarCore ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CalendarUtils ${CALENDAR_UTILS_VERSION} CONFIG REQUIRED)
find_package(KF5WebEngineViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5TemplateParser ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MailCommon ${MAILCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5MessageViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimAddressbookImportExport ${KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}TextGrammarCheck ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)
find_package(KF${KF_MAJOR_VERSION}TextTranslator ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)
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
find_package(KF${KF_MAJOR_VERSION}Contacts ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5ContactEditor ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimImportWizard ${IMPORTWIZARD_LIB_VERSION} CONFIG)
find_package(KF5MailImporterAkonadi ${MAILIMPORTER_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimPkPass ${KPIMPKPASS_LIB_VERSION} CONFIG REQUIRED)
find_package(KPimItinerary ${KPIMITINERARY_LIB_VERSION} CONFIG REQUIRED)

if (QT_MAJOR_VERSION STREQUAL "5")
    find_package(Grantlee5 "5.3" CONFIG REQUIRED)
    set(TEMPLATES_LIB Grantlee5::Templates)
else()
    find_package(KF6TextTemplate CONFIG REQUIRED)
    set(TEMPLATES_LIB KF6::TextTemplate)
endif()

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

if(KDEPIM_ENTERPRISE_BUILD)
  set(KDEPIM_ENTERPRISE_BUILD true)
else()
  set(KDEPIM_ENTERPRISE_BUILD false)
endif()

# Extra package
find_package(Gpgmepp 1.16.0 CONFIG)
set_package_properties(Gpgmepp PROPERTIES DESCRIPTION "GpgME library" URL "https://www.gnupg.org" TYPE REQUIRED)
if (QT_MAJOR_VERSION STREQUAL "5")
ecm_set_disabled_deprecation_versions(QT 5.15.0  KF 5.102.0)
else()
ecm_set_disabled_deprecation_versions(QT 6.4  KF 5.102.0)
endif()

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
           MESSAGE(STATUS "Discount ${PC_LIBMARKDOWN_VERSION}: has highlighting support")
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
