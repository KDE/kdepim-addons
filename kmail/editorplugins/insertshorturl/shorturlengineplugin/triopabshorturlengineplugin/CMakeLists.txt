set(pimcommon_triopabshorturlengineplugin_SRCS
    triopabshorturlengineplugin.cpp
    triopabshorturlengineinterface.cpp
)

kcoreaddons_add_plugin(pimcommon_triopabshorturlengineplugin SOURCES
    ${pimcommon_triopabshorturlengineplugin_SRCS} INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/pimcommon/shorturlengine)

target_link_libraries(pimcommon_triopabshorturlengineplugin
    KF5::Service KF5::I18n Qt${QT_MAJOR_VERSION}::Network KF5::CoreAddons shorturlpluginprivate  Qt${QT_MAJOR_VERSION}::Gui
)

