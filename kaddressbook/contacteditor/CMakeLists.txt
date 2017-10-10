add_definitions(-DTRANSLATION_DOMAIN=\"kaddressbook_contacteditor\")

set(contacteditor_addresslocationeditor_plugin_SRCS
    addresseditor/addresseslocationgrantleeformater.cpp
    addresseditor/addresseslocationwidget.cpp
    addresseditor/addressgrantleeobject.cpp
    addresseditor/addresslocationwidget.cpp
    addresseditor/addresstypedialog.cpp
    addresseditor/iconnamecache.cpp
    addresseditor/selectaddresstypecombobox.cpp
    addresseditor/webengine/addresseslocationenginepage.cpp
    addresseditor/webengine/addresseslocationengineviewer.cpp
    )
ecm_qt_declare_logging_category(contacteditor_addresslocationeditor_plugin_SRCS HEADER addresslocationeditorplugin_debug.h IDENTIFIER
    ADDRESSLOCATIONEDITORPLUGIN_LOG CATEGORY_NAME org.kde.pim.addresslocationeditorplugin)


#if(BUILD_TESTING)
#    add_subdirectory(addresseditor/tests)
#    add_subdirectory(addresseditor/autotests)
#endif()


set(addresslocationeditorplugin_SRCS
    addresslocationeditorplugin.cpp
    ${contacteditor_addresslocationeditor_plugin_SRCS}
    )

kcoreaddons_add_plugin(addresslocationeditorplugin JSON addresslocationeditorplugin.json SOURCES
    ${addresslocationeditorplugin_SRCS} INSTALL_NAMESPACE contacteditor)

target_link_libraries(addresslocationeditorplugin
    KF5::I18n
    KF5::AkonadiContact
    KF5::ContactEditor
    Grantlee5::Templates
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::IconThemes
    KF5::Completion
    )

add_subdirectory(addresseditor/html)
