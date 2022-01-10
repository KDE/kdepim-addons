set(pimcommon_tinyplugin_SRCS
    tinyurlengineplugin.cpp
    tinyurlengineinterface.cpp
)

kcoreaddons_add_plugin(pimcommon_tinyurlengineplugin SOURCES
    ${pimcommon_tinyplugin_SRCS} INSTALL_NAMESPACE pimcommon/shorturlengine)


target_link_libraries(pimcommon_tinyurlengineplugin
    KF5::Service KF5::I18n Qt${QT_MAJOR_VERSION}::Network KF5::CoreAddons shorturlpluginprivate Qt${QT_MAJOR_VERSION}::Gui
)

