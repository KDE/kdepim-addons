
set(folderconfiguresettings_SRCS
    folderconfiguresettingsdialog.cpp
    folderconfiguresettingswidget.cpp
    foldersettingfilterproxymodel.cpp
    folderconfiguretreewidget.cpp
    folderconfiguresettingspagewidget.cpp
    folderconfiguresettingsgeneralwidget.cpp
    folderconfiguresettingstemplatewidget.cpp
    folderconfiguresettingsviewwidget.cpp
    folderconfiguremodifycollectionjob.cpp
    folderconfiguresettingspagebase.cpp
    )

ecm_qt_declare_logging_category(folderconfiguresettings_SRCS HEADER libfolderconfiguresettings_debug.h IDENTIFIER LIBFOLDERCONFIGURESETTINGS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libfolderconfiguresettingsplugin
    DESCRIPTION "kdepim-addons (foldersettings-configure)"
    EXPORT KDEPIMADDONS
    )

add_library(folderconfiguresettings ${folderconfiguresettings_SRCS})
generate_export_header(folderconfiguresettings BASE_NAME libfolderconfiguresettings)
target_link_libraries(folderconfiguresettings
    KF5::MessageViewer
    KF5::I18n
    KF5::MailCommon
    )

set_target_properties(folderconfiguresettings
    PROPERTIES OUTPUT_NAME folderconfiguresettings VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS folderconfiguresettings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


set(messageviewer_folderconfiguresettingsplugin_SRCS
   folderconfiguresettingsplugin.cpp
)

kcoreaddons_add_plugin(messageviewer_folderconfiguresettingsplugin JSON messageviewer_folderconfiguresettingsplugin.json SOURCES
    ${messageviewer_folderconfiguresettingsplugin_SRCS} INSTALL_NAMESPACE messageviewer/configuresettings)

target_link_libraries(messageviewer_folderconfiguresettingsplugin
  KF5::MessageViewer
  KF5::I18n
  KF5::MailCommon
  folderconfiguresettings
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
