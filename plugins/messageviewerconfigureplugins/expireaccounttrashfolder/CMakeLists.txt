add_library(expireaccounttrashfolderconfig)
target_sources(expireaccounttrashfolderconfig PRIVATE
    expireaccounttrashfolderconfigdialog.cpp
    expireaccounttrashfolderconfigwidget.cpp

    )

ecm_qt_declare_logging_category(expireaccounttrashfolderconfig HEADER libexpireaccounttrashfolderconfig_debug.h IDENTIFIER LIBEXPIREACCOUNTTRASHFOLDERCONFIG_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libexpireaccounttrashfolderconfig
    DESCRIPTION "kdepim-addons (expire account trash folder config)"
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(expireaccounttrashfolderconfig PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(expireaccounttrashfolderconfig BASE_NAME libexpireaccounttrashfolderconfig)
target_link_libraries(expireaccounttrashfolderconfig
    KF5::MessageViewer
    KF5::I18n
    KF5::MailCommon
    )

set_target_properties(expireaccounttrashfolderconfig
    PROPERTIES OUTPUT_NAME expireaccounttrashfolderconfig VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS expireaccounttrashfolderconfig ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)



kcoreaddons_add_plugin(messageviewer_expireaccounttrashfolderconfigplugin INSTALL_NAMESPACE messageviewer/configuresettings)
target_sources(messageviewer_expireaccounttrashfolderconfigplugin PRIVATE
   expireaccounttrashfolderconfigplugin.cpp
)

target_link_libraries(messageviewer_expireaccounttrashfolderconfigplugin
  KF5::MessageViewer
  KF5::I18n
  KF5::MailCommon
  expireaccounttrashfolderconfig
)


if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
