if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

set(grammalecteplugin_SRCS
    grammalecteplugin.cpp
    grammalecteinterface.cpp
    )

kcoreaddons_add_plugin(kmail_grammalecteplugin JSON kmail_grammalecteplugin.json SOURCES
    ${grammalecteplugin_SRCS} INSTALL_NAMESPACE kmail)

target_link_libraries(kmail_grammalecteplugin
        KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::XmlGui libkmailgrammalecte
    )
