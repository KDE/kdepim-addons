########### next target ###############
add_library(korg_picoftheday MODULE)

target_sources(korg_picoftheday PRIVATE
    configdialog.cpp
    picoftheday.cpp
    element.cpp
    configdialog.h
    picoftheday.h
    element.h
    )
ecm_qt_declare_logging_category(korg_picoftheday HEADER korganizer_picoftheday_plugin_debug.h IDENTIFIER KORGANIZERPICOFTHEDAYPLUGIN_LOG CATEGORY_NAME org.kde.pim.korganizer_picoftheday_plugins
    DESCRIPTION "kdepim-addons (korganizer picoftheday plugins)"
    OLD_CATEGORY_NAMES log_korganizer_picoftheday_plugins
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(korg_picoftheday PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(korg_picoftheday
    PRIVATE
    KF5::EventViews
    KF5::KIOCore
    Qt${QT_MAJOR_VERSION}::Xml
    )

install(TARGETS
    korg_picoftheday
    DESTINATION ${KDE_INSTALL_PLUGINDIR}
    )

########### install files ###############

install(FILES
    picoftheday.desktop
    DESTINATION ${KDE_INSTALL_KSERVICES5DIR}/korganizer
    )

