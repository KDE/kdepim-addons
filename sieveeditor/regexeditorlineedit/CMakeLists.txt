include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(sieveeditorregexp_plugin_categories_SRCS)
ecm_qt_declare_logging_category(sieveeditorregexp_plugin_categories_SRCS HEADER regexpeditorlineeditplugin_debug.h IDENTIFIER
    REGEXPEDITORLINEEDITPLUGIN_LOG CATEGORY_NAME org.kde.pim.regexpeditorlineedit
    DESCRIPTION "kdepim-addons (SieveEditor Regexp Editor plugin)"
    EXPORT KDEPIMADDONS
    )


if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()


set(regexpeditorlineeditplugin_SRCS
    regexpeditorlineedit.cpp
    ${sieveeditorregexp_plugin_categories_SRCS}
    )

kcoreaddons_add_plugin(regexpeditorlineeditplugin JSON regexepeditorlineedit.json SOURCES
    ${regexpeditorlineeditplugin_SRCS} INSTALL_NAMESPACE libksieve)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(regexpeditorlineeditplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(regexpeditorlineeditplugin
    KF5::I18n KF5::KSieveUi KF5::TextWidgets KF5::Service
    )
