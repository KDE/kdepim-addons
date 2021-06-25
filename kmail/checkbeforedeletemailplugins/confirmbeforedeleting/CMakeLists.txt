if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
kcoreaddons_add_plugin(kmail_confirmbeforedeletingplugin JSON kmail_confirmbeforedeletingplugin.json INSTALL_NAMESPACE messageviewer/checkbeforedeleting)
target_sources(kmail_confirmbeforedeletingplugin PRIVATE
    confirmbeforedeletinginterface.cpp
    )

ecm_qt_declare_logging_category(kmail_confirmbeforedeletingplugin HEADER confirmbeforedeletingplugin_debug.h IDENTIFIER KMAIL_CONFIRMBEFOREDELETING_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_confirmbeforedeletingplugin
    DESCRIPTION "kdepim-addons (Confirm Before Deleting email)"
    OLD_CATEGORY_NAMES log_kmail_confirmbeforedeletingplugin
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_confirmbeforedeletingplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_confirmbeforedeletingplugin
    KF5::MessageViewer KF5::I18n KF5::PimCommon KF5::Libkdepim
    )
