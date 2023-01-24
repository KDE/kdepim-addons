set(pimcommon_triopabshorturlengineplugin_SRCS
    triopabshorturlengineplugin.cpp
    triopabshorturlengineinterface.cpp
    triopabshorturlengineplugin.h
    triopabshorturlengineinterface.h
)

kcoreaddons_add_plugin(pimcommon_triopabshorturlengineplugin SOURCES
    ${pimcommon_triopabshorturlengineplugin_SRCS} INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/pimcommon/shorturlengine)

target_link_libraries(pimcommon_triopabshorturlengineplugin
    KF${KF_MAJOR_VERSION}::Service KF${KF_MAJOR_VERSION}::I18n Qt::Network KF${KF_MAJOR_VERSION}::CoreAddons shorturlpluginprivate  Qt::Gui
)

