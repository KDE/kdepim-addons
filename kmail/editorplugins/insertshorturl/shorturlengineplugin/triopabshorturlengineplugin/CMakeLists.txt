set(pimcommon_triopabshorturlengineplugin_SRCS
    triopabshorturlengineplugin.cpp
    triopabshorturlengineinterface.cpp
    triopabshorturlengineplugin.h
    triopabshorturlengineinterface.h
)

kcoreaddons_add_plugin(pimcommon_triopabshorturlengineplugin SOURCES
    ${pimcommon_triopabshorturlengineplugin_SRCS} INSTALL_NAMESPACE pim6/pimcommon/shorturlengine
)

target_link_libraries(
    pimcommon_triopabshorturlengineplugin
    KF6::Service
    KF6::I18n
    Qt::Network
    KF6::CoreAddons
    shorturlpluginprivate
    Qt::Gui
)
