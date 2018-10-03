cmake_minimum_required(VERSION 3.1)

project(%{ProjectName})

set(KF5_VERSION "5.50.0")
set(QT_REQUIRED_VERSION "5.9.0")

find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

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
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)


find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test)

find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5XmlGui ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_VERSION} CONFIG REQUIRED)


set(MESSAGELIB_LIB_VERSION "5.9.0")

find_package(KF5MessageComposer ${MESSAGELIB_LIB_VERSION} CONFIG REQUIRED)

set(%{ProjectName}_SRCS
    %{ProjectName}plugineditor.cpp
    %{ProjectName}plugineditorinterface.cpp
)

ecm_qt_declare_logging_category(%{ProjectName}_SRCS HEADER %{ProjectName}editorplugin_debug.h IDENTIFIER %{DebugIdentifierName} CATEGORY_NAME %{DebugCategoryName})

kcoreaddons_add_plugin(%{ProjectName} JSON %{ProjectName}editorplugin.json SOURCES
    ${%{ProjectName}_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(%{ProjectName}
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

