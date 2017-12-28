set(pimcommon_tinyplugin_SRCS
    tinyurlengineplugin.cpp
    tinyurlengineinterface.cpp
)

kcoreaddons_add_plugin(pimcommon_tinyurlengineplugin JSON pimcommon_tinyurlengineplugin.json SOURCES
    ${pimcommon_tinyplugin_SRCS} INSTALL_NAMESPACE pimcommon)


target_link_libraries(pimcommon_tinyurlengineplugin
    KF5::Service KF5::I18n Qt5::Network KF5::CoreAddons shorturlpluginprivate Qt5::Gui
)

