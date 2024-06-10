# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "6.1.40")

project(kdepim-addons VERSION ${PIM_VERSION})

set(KF_MIN_VERSION "6.3.0")
set(QT_REQUIRED_VERSION "6.6.0")
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
set(KDEPIMADDONS_LIB_SOVERSION "6")

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


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
include(ECMFeatureSummary)
set(KTEXTADDONS_MIN_VERSION "1.5.4")

option(KDEPIM_ENTERPRISE_BUILD "Enable features specific to the enterprise branch, which are normally disabled. Also, it disables many components not needed for Kontact such as the Kolab client." FALSE)


find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED WebEngineWidgets Widgets Test)

find_package(KF6I18n ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Config ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6DBusAddons ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6XmlGui ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Declarative ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6SyntaxHighlighting ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6KIO ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6IconThemes ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Parts ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Prison ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6Holidays ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6GuiAddons ${KF_MIN_VERSION} CONFIG REQUIRED)

set(MAILCOMMON_LIB_VERSION "6.1.40")
set(GRAVATAR_LIB_VERSION "6.1.40")
set(PIMCOMMON_LIB_VERSION "6.1.40")
set(GRANTLEETHEME_LIB_VERSION "6.1.40")
set(CALENDARSUPPORT_LIB_VERSION "6.1.40")
set(EVENTVIEW_LIB_VERSION "6.1.40")
set(LIBKDEPIM_LIB_VERSION "6.1.40")
set(KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION "6.1.40")
set(LIBKLEO_LIB_VERSION "6.1.40")
set(AKONADI_LIB_VERSION "6.1.40")
set(INCIDENCEEDITOR_LIB_VERSION "6.1.40")
set(KTNEF_LIB_VERSION "6.1.40")
set(MESSAGELIB_LIB_VERSION "6.1.40")
set(AKONADICALENDAR_LIB_VERSION "6.1.40")
set(CALENDAR_UTILS_VERSION "6.1.40")
set(KPIMTEXTEDIT_LIB_VERSION "6.1.40")
set(KIMAP_LIB_VERSION "6.1.40")
set(LIBKSIEVE_LIB_VERSION "6.1.40")
set(KMAILTRANSPORT_LIB_VERSION "6.1.40")
set(AKONADICONTACT_LIB_VERSION "6.1.40")
set(IMPORTWIZARD_LIB_VERSION "6.1.40")
set(MAILIMPORTER_LIB_VERSION "6.1.40")
set(KPIMPKPASS_LIB_VERSION "6.1.40")
set(KPIMITINERARY_LIB_VERSION "6.1.40")
set(AKONADINOTES_LIB_VERSION "6.1.40")
set(KPIM_MIME_VERSION "6.1.40")

set(KLLMCORE_VERSION "0.1.0")
find_package(KPim6Mime ${KPIM_MIME_VERSION} CONFIG REQUIRED)
find_package(KPim6AkonadiNotes ${AKONADINOTES_LIB_VERSION} CONFIG REQUIRED)
find_package(KF6CalendarCore ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KPim6CalendarUtils ${CALENDAR_UTILS_VERSION} CONFIG REQUIRED)
find_package(KPim6WebEngineViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6TemplateParser ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MailCommon ${MAILCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MessageViewer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6AddressbookImportExport ${KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)
find_package(KF6TextGrammarCheck ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6TextTranslator ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6TextAddonsWidgets ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6TextUtils ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)
find_package(KPim6Libkdepim ${LIBKDEPIM_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6IncidenceEditor ${INCIDENCEEDITOR_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MessageCore ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MessageComposer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MessageList ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6CalendarSupport ${CALENDARSUPPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6EventViews ${EVENTVIEW_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6Akonadi ${AKONADI_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6AkonadiCalendar ${AKONADICALENDAR_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6Gravatar ${GRAVATAR_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6TextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6IdentityManagementCore ${KIDENTITYMANAGEMENT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6KSieveUi ${LIBKSIEVE_LIB_VERSION} CONFIG REQUIRED)
find_package(KF6TextCustomEditor ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)

find_package(KPim6Tnef ${KTNEF_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MailTransport ${KMAILTRANSPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF6Contacts ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KPim6AkonadiContactWidgets ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6ImportWizard ${IMPORTWIZARD_LIB_VERSION} CONFIG)
find_package(KPim6MailImporterAkonadi ${MAILIMPORTER_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6PkPass ${KPIMPKPASS_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6Itinerary ${KPIMITINERARY_LIB_VERSION} CONFIG REQUIRED)

find_package(KF6TextTemplate CONFIG REQUIRED)

find_package(KLLMCore ${KLLMCORE_VERSION})
set_package_properties(KLLMCore PROPERTIES
    TYPE OPTIONAL
    PURPOSE "Required for building IA plugins support"
    DESCRIPTION "Use local IA plugin"
    URL https://invent.kde.org/utilities/alpaka
)

# For adblocker
find_package(Corrosion)
set_package_properties(Corrosion PROPERTIES
    TYPE RECOMMENDED
    PURPOSE "Required to build the builtin adblocker"
    DESCRIPTION "CMake scripts to seamlessly build and link to targets using cargo"
    URL https://github.com/corrosion-rs/corrosion
)

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)

if(KDEPIM_ENTERPRISE_BUILD)
  set(KDEPIM_ENTERPRISE_BUILD true)
else()
  set(KDEPIM_ENTERPRISE_BUILD false)
endif()
add_definitions(-DQT_NO_CONTEXTLESS_CONNECT)
# Extra package
find_package(Gpgmepp 1.16.0 CONFIG)
set_package_properties(Gpgmepp PROPERTIES DESCRIPTION "GpgME library" URL "https://www.gnupg.org" TYPE REQUIRED)
ecm_set_disabled_deprecation_versions(QT 6.7.0 KF 6.3.0)

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

option(BUILD_SCAM_SETTINGS_PLUGINS "Build scam settings plugins (In progress)" OFF)

add_subdirectory(plugins)
add_subdirectory(korganizer)
add_subdirectory(kmail)
add_subdirectory(kaddressbook)
add_subdirectory(sieveeditor)
add_subdirectory(kmailtransport)
if (TARGET KPim6::ImportWizard)
  add_subdirectory(akonadi-import-wizard)
endif()

ecm_qt_install_logging_categories(
    EXPORT KDEPIMADDONS
    FILE kdepim-addons.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
    )
kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ki18n_install(po)
ecm_feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
