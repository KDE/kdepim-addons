kcoreaddons_add_plugin(messageviewer_externalscriptplugin
    INSTALL_NAMESPACE messageviewer/viewerplugin)
target_sources(messageviewer_externalscriptplugin PRIVATE
    viewerpluginexternalscript.cpp
    viewerpluginexternalscriptinterface.cpp
    viewerpluginexternalscriptmanager.cpp
    viewerpluginexternalscriptinfo.cpp
    viewerpluginexternalscriptsloadjob.cpp
    viewerpluginexternalscriptparseargument.cpp
    configuredialog/viewerpluginexternalconfiguredialog.cpp
    configuredialog/viewerpluginexternalconfigurewidget.cpp
    configuredialog/viewerpluginexternaleditdialog.cpp
    configuredialog/viewerpluginexternaleditwidget.cpp
    )


ecm_qt_declare_logging_category(messageviewer_externalscriptplugin HEADER externalscriptplugin_debug.h IDENTIFIER EXTERNALSCRIPTPLUGIN_LOG CATEGORY_NAME org.kde.pim.externalscriptplugin
    DESCRIPTION "kdepim-addons (External Script Plugin)"
    OLD_CATEGORY_NAMES log_externalscriptplugin
    EXPORT KDEPIMADDONS
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_externalscriptplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_externalscriptplugin
    KF5::MessageViewer KF5::XmlGui KF5::I18n KF5::PimCommon KF5::KIOWidgets KF5::Libkdepim
    )

if (KDEPIMADDONS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif() 

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
