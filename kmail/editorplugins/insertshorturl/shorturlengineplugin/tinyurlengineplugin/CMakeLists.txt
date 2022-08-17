set(pimcommon_tinyplugin_SRCS
    tinyurlengineplugin.cpp
    tinyurlengineinterface.cpp
    tinyurlengineplugin.h
    tinyurlengineinterface.h
)

kcoreaddons_add_plugin(pimcommon_tinyurlengineplugin SOURCES
    ${pimcommon_tinyplugin_SRCS} INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/pimcommon/shorturlengine)


target_link_libraries(pimcommon_tinyurlengineplugin
    KF5::Service KF5::I18n Qt::Network KF5::CoreAddons shorturlpluginprivate Qt::Gui
)

