include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_BINARY_DIR}/
)

set(DISCOUNT_HAS_HIGHLIGHTING_SUPPORT ${DISCOUNT_HAS_HIGHLIGHTING_SUPPORT})
configure_file(config-markdownplugin.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-markdownplugin.h )


set(kmail_markdownplugin_SRCS
    markdowninterface.cpp
    markdownplugin.cpp
    markdownpreviewwidget.cpp
    markdownconfigurewidget.cpp
    markdownconfiguredialog.cpp
    markdownconverter.cpp
    markdownpreviewdialog.cpp
    markdownenginepage.cpp
    markdowncreatelinkwidget.cpp
    markdowncreatelinkdialog.cpp
    markdowncreateimagewidget.cpp
    markdowncreateimagedialog.cpp
    markdownhighlighter.cpp
    markdownutil.cpp
    )


ecm_qt_declare_logging_category(kmail_markdownplugin_SRCS HEADER markdownplugin_debug.h IDENTIFIER KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_markdownplugin)



kcoreaddons_add_plugin(kmail_markdownplugin JSON kmail_markdownplugin.json SOURCES
    ${kmail_markdownplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_markdownplugin PRIVATE
    KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::XmlGui Qt5::WebEngineWidgets  discount::Lib KF5::SyntaxHighlighting
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
