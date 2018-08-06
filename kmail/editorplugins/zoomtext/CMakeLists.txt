set(kmail_zoomtexteditorplugin_SRCS
    zoomtextplugineditor.cpp
    zoomtextplugineditorinterface.cpp
    zoomlabel.cpp
)

ecm_qt_declare_logging_category(kmail_zoomtexteditorplugin_SRCS HEADER zoomtexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_ZOOMTEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_zoomtexteditorplugin)


kcoreaddons_add_plugin(kmail_zoomtexteditorplugin JSON kmail_zoomtexteditorplugin.json SOURCES
    ${kmail_zoomtexteditorplugin_SRCS} INSTALL_NAMESPACE kmail)


target_link_libraries(kmail_zoomtexteditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui KF5::I18n
)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

