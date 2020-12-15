set(kmail_confirmaddresseditorplugin_SRCS
    confirmaddressinterface.cpp
    confirmaddressplugin.cpp
    confirmaddressconfigurewidget.cpp
    confirmaddressdialog.cpp
    confirmaddresswidget.cpp
    confirmaddressconfiguretabwidget.cpp
    confirmaddressconfiguretab.cpp
    confirmaddresscheckjob.cpp
    confirmaddressconfiguredialog.cpp
    confirmaddresssimplestringlisteditor.cpp
    confirmaddressemailentrydialog.cpp
    )

ecm_qt_declare_logging_category(kmail_confirmaddresseditorplugin_SRCS HEADER confirmaddressplugin_debug.h IDENTIFIER KMAIL_EDITOR_CONFIRMADDRESS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_confirmaddressplugin
    DESCRIPTION "kdepim-addons (Confirm Address plugin)"
    OLD_CATEGORY_NAMES log_kmail_confirmaddressplugin
    EXPORT KDEPIMADDONS
    )

kcoreaddons_add_plugin(kmail_confirmaddresseditorplugin JSON kmail_confirmaddressplugin.json SOURCES
    ${kmail_confirmaddresseditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugincheckbeforesend)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_confirmaddresseditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_confirmaddresseditorplugin
    KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::Libkdepim
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

