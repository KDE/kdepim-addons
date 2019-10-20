set(kmail_autocorrectioneditorplugin_SRCS
    autocorrectionplugineditor.cpp
    autocorrectionplugineditorinterface.cpp
    )

kcoreaddons_add_plugin(kmail_autocorrectioneditorplugin JSON kmail_autocorrectioneditorplugin.json SOURCES ${kmail_autocorrectioneditorplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_autocorrectioneditorplugin
    KF5::MessageComposer KF5::XmlGui KF5::I18n
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

