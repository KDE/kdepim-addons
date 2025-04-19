# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "6.4.1")

project(kdepim-addons VERSION ${PIM_VERSION})

set(KF_MIN_VERSION "6.9.0")
set(QT_REQUIRED_VERSION "6.7.0")
find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/ ${ECM_MODULE_PATH})

# Do NOT add quote
set(KDEPIM_DEV_VERSION)

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

include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES 
	examples/*.cpp 
	examples/*.h 
	examples/*.c
	kmailtransport/*.cpp
        kmailtransport/*.h
        kmailtransport/*.c
        plugins/*.cpp
        plugins/*.h
        plugins/*.c
        sieveeditor/*.cpp
        sieveeditor/*.h
        sieveeditor/*.c
        akonadi-import-wizard/*.cpp
        akonadi-import-wizard/*.h
        akonadi-import-wizard/*.c	
        kaddressbook/*.cpp
        kaddressbook/*.h
        kaddressbook/*.c
        kmail/*.cpp
        kmail/*.h
        kmail/*.c
        korganizer/*.cpp
        korganizer/*.h
        korganizer/*.c
	kldap/*.cpp
	kldap/*.h
)

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
find_package(KF6ConfigWidgets ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF6ColorScheme ${KF_MIN_VERSION} CONFIG REQUIRED)
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
find_package(KF6ColorScheme ${KF_MIN_VERSION} CONFIG REQUIRED)
if(NOT WIN32)
   find_package(KF6KCMUtils ${KF_MIN_VERSION} CONFIG REQUIRED)
endif()   

set(MAILCOMMON_LIB_VERSION "6.4.1")
set(GRAVATAR_LIB_VERSION "6.4.1")
set(PIMCOMMON_LIB_VERSION "6.4.1")
set(GRANTLEETHEME_LIB_VERSION "6.4.1")
set(CALENDARSUPPORT_LIB_VERSION "6.4.1")
set(LIBKDEPIM_LIB_VERSION "6.4.1")
set(KADDRESSBOOK_IMPORTEXPORT_LIB_VERSION "6.4.1")
set(LIBKLEO_LIB_VERSION "6.4.1")
set(AKONADI_LIB_VERSION "6.4.1")
set(INCIDENCEEDITOR_LIB_VERSION "6.4.1")
set(KTNEF_LIB_VERSION "6.4.1")
set(MESSAGELIB_LIB_VERSION "6.4.1")
set(AKONADICALENDAR_LIB_VERSION "6.4.1")
set(CALENDAR_UTILS_VERSION "6.4.1")
set(KPIMTEXTEDIT_LIB_VERSION "6.4.1")
set(KIMAP_LIB_VERSION "6.4.1")
set(LIBKSIEVE_LIB_VERSION "6.4.1")
set(KMAILTRANSPORT_LIB_VERSION "6.4.1")
set(AKONADICONTACT_LIB_VERSION "6.4.1")
set(IMPORTWIZARD_LIB_VERSION "6.4.1")
set(MAILIMPORTER_LIB_VERSION "6.4.1")
set(KPIMPKPASS_LIB_VERSION "6.4.1")
set(KPIMITINERARY_LIB_VERSION "6.4.1")
set(KPIM_MIME_VERSION "6.4.1")
set(KLDAP_LIB_VERSION "6.4.1")

find_package(KPim6Mime ${KPIM_MIME_VERSION} CONFIG REQUIRED)
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
find_package(KPim6PimCommonActivities ${PIMCOMMON_LIB_VERSION} CONFIG)
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
find_package(KPim6Akonadi ${AKONADI_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6AkonadiCalendar ${AKONADICALENDAR_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6Gravatar ${GRAVATAR_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6TextEdit ${KPIMTEXTEDIT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6IdentityManagementCore ${KIDENTITYMANAGEMENT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6IMAP ${KIMAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6KSieveUi ${LIBKSIEVE_LIB_VERSION} CONFIG REQUIRED)
find_package(KF6TextCustomEditor ${KTEXTADDONS_MIN_VERSION} CONFIG REQUIRED)

find_package(KF6TextAutogenerateText ${KTEXTADDONS_MIN_VERSION} CONFIG)
set_package_properties(KF6TextAutogenerateText PROPERTIES
    TYPE OPTIONAL
    PURPOSE "Required for building AI plugins support"
    DESCRIPTION "Use AI plugin"
)


find_package(KPim6Tnef ${KTNEF_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6MailTransport ${KMAILTRANSPORT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF6Contacts ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KPim6AkonadiContactWidgets ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6ImportWizard ${IMPORTWIZARD_LIB_VERSION} CONFIG)
find_package(KPim6MailImporterAkonadi ${MAILIMPORTER_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6PkPass ${KPIMPKPASS_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6Itinerary ${KPIMITINERARY_LIB_VERSION} CONFIG REQUIRED)
find_package(KPim6LdapWidgets ${KLDAP_LIB_VERSION} CONFIG REQUIRED)
find_package(KF6TextTemplate CONFIG REQUIRED)

if(TARGET KPim6::PimCommonActivities)
    option(OPTION_USE_PLASMA_ACTIVITIES "Activate plasma activities" ON)
    if(OPTION_USE_PLASMA_ACTIVITIES)
        if(NOT WIN32 AND NOT APPLE)
            set(OPTION_USE_PLASMA_ACTIVITIES true)
        else()
            set(OPTION_USE_PLASMA_ACTIVITIES false)
        endif()
    endif()
    if(OPTION_USE_PLASMA_ACTIVITIES)
        if(NOT WIN32 AND NOT APPLE)
            find_package(PlasmaActivities "6.1.0")
            set_package_properties(PlasmaActivities PROPERTIES DESCRIPTION
                "Allow to compile with plasma activities"
                TYPE OPTIONAL
            )
        endif()

        if(TARGET Plasma::Activities)
            set(KDEPIM_ADDONS_HAVE_ACTIVITY_SUPPORT TRUE)
        endif()
    endif()
endif()

configure_file(config-kdepim-addons.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-kdepim-addons.h)

# For adblocker
find_package(Corrosion CONFIG)
set_package_properties(Corrosion PROPERTIES
    TYPE RECOMMENDED
    PURPOSE "Required to build the builtin adblocker"
    DESCRIPTION "CMake scripts to seamlessly build and link to targets using cargo"
    URL https://github.com/corrosion-rs/corrosion
)

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif()

if(KDEPIM_ENTERPRISE_BUILD)
  set(KDEPIM_ENTERPRISE_BUILD true)
else()
  set(KDEPIM_ENTERPRISE_BUILD false)
endif()
add_definitions(-DQT_NO_CONTEXTLESS_CONNECT)
# Extra package
find_package(Gpgmepp 1.23.2 CONFIG)
set_package_properties(Gpgmepp PROPERTIES DESCRIPTION "GpgME library" URL "https://www.gnupg.org" TYPE REQUIRED)
ecm_set_disabled_deprecation_versions(QT 6.9.0 KF 6.12.0)

option(KDEPIM_RUN_AKONADI_TEST "Enable autotest based on Akonadi." TRUE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(QTCREATOR_TEMPLATE_INSTALL_DIR ${KDE_INSTALL_DATADIR}/qtcreator/templates CACHE PATH "Define qtcreator template install path (default is /usr/share/qtcreator/templates)")

find_package(Discount "2" MODULE)
set_package_properties("discount" PROPERTIES
        DESCRIPTION "A library that gives you formatting functions suitable for marking down entire documents or lines of text"
        URL "https://www.pell.portland.or.us/~orc/Code/discount/"
        TYPE RECOMMENDED
        PURPOSE "Generate Markdown file.")

if(discount_FOUND)
   if(DEFINED PC_LIBMARKDOWN_VERSION)
      if(${PC_LIBMARKDOWN_VERSION} VERSION_GREATER "2.2.5")
           set(DISCOUNT_HAS_HIGHLIGHTING_SUPPORT TRUE)
           message(STATUS "Discount ${PC_LIBMARKDOWN_VERSION}: has highlighting support")

           # in 3.0.0d, the signature for mkd_e_code_format changed
           if(${PC_LIBMARKDOWN_VERSION} VERSION_GREATER_EQUAL "3.0.0")
               if(${PC_LIBMARKDOWN_VERSION} MATCHES "[abc]$")
                   set(DISCOUNT_NEW_HIGHLIGHTING_SIGNATURE FALSE)
               else()
                   set(DISCOUNT_NEW_HIGHLIGHTING_SIGNATURE TRUE)
               endif()
           endif()
      endif()
   endif()
endif()

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if(USE_UNITY_CMAKE_SUPPORT)
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
add_subdirectory(kldap)
if(TARGET KPim6::ImportWizard)
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
