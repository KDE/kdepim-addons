set(pimcommon_triopabshorturlengineplugin_SRCS
    triopabshorturlengineplugin.cpp
    triopabshorturlengineinterface.cpp
)

kcoreaddons_add_plugin(pimcommon_triopabshorturlengineplugin JSON pimcommon_triopabshorturlengineplugin.json SOURCES
    ${pimcommon_triopabshorturlengineplugin_SRCS} INSTALL_NAMESPACE pimcommon/shorturlengine)

target_link_libraries(pimcommon_triopabshorturlengineplugin
    KF5::Service KF5::I18n Qt::Network KF5::CoreAddons shorturlpluginprivate  Qt5::Gui
)

