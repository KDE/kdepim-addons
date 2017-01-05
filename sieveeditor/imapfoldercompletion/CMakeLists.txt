include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(sieveeditor_plugin_categories_SRCS)
ecm_qt_declare_logging_category(sieveeditor_plugin_categories_SRCS HEADER imapfoldercompletionplugin_debug.h IDENTIFIER
    IMAPFOLDERCOMPLETIONPLUGIN_LOG CATEGORY_NAME org.kde.pim.imapfoldercompletion)

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()


set(imapfoldercompletionplugin_SRCS
    selectimapfolderdialog.cpp
    selectimapfolderwidget.cpp
    selectimapwidget.cpp
    selectitemfolderjob.cpp
    selectimapfoldermodel.cpp
    selectimaplineedit.cpp
    selectimaplineeditcompletermodel.cpp
    ${sieveeditor_plugin_categories_SRCS}
    )

kcoreaddons_add_plugin(imapfoldercompletionplugin JSON imapfoldercompletion.json SOURCES
    ${imapfoldercompletionplugin_SRCS} INSTALL_NAMESPACE libksieve)

target_link_libraries(imapfoldercompletionplugin
    KF5::PimCommon KF5::Completion KF5::I18n KF5::KIOWidgets KF5::KSieveUi KF5::MailTransport KF5::IMAP
    )
