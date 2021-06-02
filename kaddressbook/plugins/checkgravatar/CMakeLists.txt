include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    )

set(kaddressbook_checkgravatarplugin_SRCS
    gravatar/job/gravatarupdatejob.cpp
    gravatar/widgets/gravatarupdatedialog.cpp
    gravatar/widgets/gravatarupdatewidget.cpp

    checkgravatarplugininterface.cpp
    checkgravatarplugin.cpp
    )

ecm_qt_declare_logging_category(kaddressbook_checkgravatarplugin_SRCS HEADER kaddressbook_checkgravatarplugin_debug.h IDENTIFIER KADDRESSBOOK_CHECKGRAVATAR_LOG CATEGORY_NAME org.kde.pim.kaddressbook_checkgravatar
    DESCRIPTION "kdepim-addons (kaddressbook gravatar plugin)"
    EXPORT KDEPIMADDONS
    )


kcoreaddons_add_plugin(kaddressbook_checkgravatarplugin JSON kaddressbook_checkgravatarplugin.json SOURCES
    ${kaddressbook_checkgravatarplugin_SRCS} INSTALL_NAMESPACE kaddressbook/mainview)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kaddressbook_checkgravatarplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kaddressbook_checkgravatarplugin
    KF5::PimCommon KF5::Completion  KF5::PimCommonAkonadi KF5::XmlGui KF5::Gravatar KF5::I18n KF5::Contacts
    )

if (BUILD_TESTING)
    add_subdirectory(gravatar/autotests)
    add_subdirectory(gravatar/tests)
endif()
