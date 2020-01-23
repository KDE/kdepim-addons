set(messageviewer_dkimconfigplugin_SRCS
   dkimconfiguresettingsplugin.cpp
)

kcoreaddons_add_plugin(messageviewer_dkimconfigplugin JSON messageviewer_dkimconfigplugin.json SOURCES
    ${messageviewer_dkimconfigplugin_SRCS} INSTALL_NAMESPACE messageviewer/configuresettings)

target_link_libraries(messageviewer_dkimconfigplugin
  KF5::MessageViewer
  KF5::I18n
  dkimverifyconfigure
  )


set(dkimverifyconfigure_SRCS
    dkimconfiguredialog.cpp
    dkimconfiguretab.cpp
    dkimconfigurewidget.cpp
    dkimgeneralwidget.cpp
    dkimkeyrecordwidget.cpp
    dkimadvancedwidget.cpp
    dkimpolicywidget.cpp
    dkimauthenticationverifiedserverwidget.cpp
    dkimauthenticationverifiedserverdialog.cpp
)

ecm_qt_declare_logging_category(dkimverifyconfigure_SRCS HEADER libdkimverifyconfigure_debug.h IDENTIFIER LIBDKIMVERIFYCONFIGURE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libdkimconfigureplugin)

add_library(dkimverifyconfigure ${dkimverifyconfigure_SRCS})
generate_export_header(dkimverifyconfigure BASE_NAME libdkimverifyconfigure)
target_link_libraries(dkimverifyconfigure
    KF5::I18n
    KF5::ConfigCore
    KF5::WidgetsAddons
    KF5::MessageViewer
    KF5::ItemViews
    )

set_target_properties(dkimverifyconfigure
    PROPERTIES OUTPUT_NAME dkimverifyconfigure VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS dkimverifyconfigure ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
