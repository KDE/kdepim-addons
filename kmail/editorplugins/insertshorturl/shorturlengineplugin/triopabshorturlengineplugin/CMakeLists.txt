set(pimcommon_triopabshorturlengineplugin_SRCS
    triopabshorturlengineplugin.cpp
    triopabshorturlengineinterface.cpp
    triopabshorturlengineplugin.h
    triopabshorturlengineinterface.h
)

kcoreaddons_add_plugin(pimcommon_triopabshorturlengineplugin SOURCES
    ${pimcommon_triopabshorturlengineplugin_SRCS} INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/pimcommon/shorturlengine)

target_link_libraries(pimcommon_triopabshorturlengineplugin
    KF5::Service KF5::I18n Qt::Network KF5::CoreAddons shorturlpluginprivate  Qt::Gui
)

