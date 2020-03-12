include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(sieveeditoremaillinedit_plugin_categories_SRCS)
ecm_qt_declare_logging_category(sieveeditoremaillinedit_plugin_categories_SRCS HEADER sieveeditoremaillineditplugin_debug.h IDENTIFIER
    EMAILLINEEDITPLUGIN_LOG CATEGORY_NAME org.kde.pim.sieveeditoremaillinedit
    DESCRIPTION "kdepim-addons (SieveEditor email line plugin)"
    EXPORT KDEPIMADDONS
    )


if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()

set(sieveeditoremaillineditplugin_SRCS
    emaillineedit.cpp
    ${sieveeditoremaillinedit_plugin_categories_SRCS}
    )

kcoreaddons_add_plugin(emaillineeditplugin JSON emaillineedit.json SOURCES
    ${sieveeditoremaillineditplugin_SRCS} INSTALL_NAMESPACE libksieve)

target_link_libraries(emaillineeditplugin
    KF5::I18n KF5::KSieveUi KF5::AkonadiContact
    )



