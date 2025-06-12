set(pimcommon_tinyplugin_SRCS
    tinyurlengineplugin.cpp
    tinyurlengineinterface.cpp
    tinyurlengineplugin.h
    tinyurlengineinterface.h
)

kcoreaddons_add_plugin(pimcommon_tinyurlengineplugin SOURCES
    ${pimcommon_tinyplugin_SRCS} INSTALL_NAMESPACE pim6/pimcommon/shorturlengine
)

target_link_libraries(
    pimcommon_tinyurlengineplugin
    KF6::Service
    KF6::I18n
    Qt::Network
    KF6::CoreAddons
    shorturlpluginprivate
    Qt::Gui
)
