set(kmail_externalcomposereditorplugin_SRCS
    externalcomposerplugineditor.cpp
    externalcomposerplugineditorinterface.cpp
    externalcomposerconfiguredialog.cpp
    externalcomposerconfigurewidget.cpp
    )

kcoreaddons_add_plugin(kmail_externalcomposereditorplugin JSON kmail_externalcomposereditorplugin.json SOURCES
    ${kmail_externalcomposereditorplugin_SRCS} INSTALL_NAMESPACE kmail/plugineditorinit)

target_link_libraries(kmail_externalcomposereditorplugin
    KF5::MessageComposer KF5::XmlGui KF5::I18n KF5::KIOWidgets
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

