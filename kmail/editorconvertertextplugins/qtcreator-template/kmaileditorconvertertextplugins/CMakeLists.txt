cmake_minimum_required(VERSION 3.5)

project(%{ProjectName})

set(KF_MIN_VERSION "5.50.0")
set(QT_REQUIRED_VERSION "5.9.0")

find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMAddTests)
include(ECMMarkNonGuiExecutable)
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


find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)

find_package(KF5I18n ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF_MIN_VERSION} CONFIG REQUIRED)


set(MESSAGELIB_LIB_VERSION "5.9.0")

find_package(KF5MessageComposer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)


set(%{ProjectNameUpper}_SRCS
    %{ProjectNameLower}plugineditor.cpp
    %{ProjectNameLower}plugineditorinterface.cpp
)

ecm_qt_declare_logging_category(%{ProjectNameUpper}_SRCS HEADER %{ProjectNameLower}editorplugin_debug.h IDENTIFIER %{DebugIdentifierName} CATEGORY_NAME %{DebugCategoryName})

kcoreaddons_add_plugin(%{ProjectNameLower}editorplugin JSON %{ProjectNameLower}editorplugin.json SOURCES
    ${%{ProjectNameUpper}_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(%{ProjectNameLower}editorplugin
   KF5::MessageComposer KF5::XmlGui KF5::I18n
)


