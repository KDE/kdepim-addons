set(kmail_quicktextplugin_private_SRCS
    quicktextmenu.cpp
    quicktextconfigurewidget.cpp
    quicktextconfiguredialog.cpp
    quicktextmanager.cpp
    quicktexttreewidget.cpp
    quicktextwidget.cpp
)


add_library(kmailquicktextpluginprivate ${kmail_quicktextplugin_private_SRCS})
generate_export_header(kmailquicktextpluginprivate BASE_NAME quicktext)

target_link_libraries(kmailquicktextpluginprivate
PRIVATE
    KF5::I18n KF5::CoreAddons Qt5::Gui Qt5::Widgets KF5::MessageComposer KF5::MailCommon KF5::XmlGui
)

set_target_properties(kmailquicktextpluginprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS kmailquicktextpluginprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
set(kmail_quicktextplugin_SRCS
    quicktextplugineditor.cpp
    quicktextplugineditorinterface.cpp
)

ecm_qt_declare_logging_category(kmail_quicktextplugin_SRCS HEADER quicktextplugin_debug.h IDENTIFIER KMAIL_EDITOR_QUICKTEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_quicktextplugin)

kcoreaddons_add_plugin(kmail_quicktextplugin JSON kmail_quicktextplugin.json SOURCES
    ${kmail_quicktextplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_quicktextplugin
  KF5::MessageComposer KF5::XmlGui KF5::I18n kmailquicktextpluginprivate KF5::MailCommon
)
