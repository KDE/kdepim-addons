set(pimcommon_ur1cashorturlengineplugin_SRCS
    ur1cashorturlengineplugin.cpp
    ur1cashorturlengineinterface.cpp
)
ecm_qt_declare_logging_category(pimcommon_ur1cashorturlengineplugin_SRCS HEADER ur1cashorturlengineplugin_debug.h
    IDENTIFIER UR1CASHORTURLENGINEPLUGIN_LOG CATEGORY_NAME org.kde.pim.ur1cashorturlengineplugin)

kcoreaddons_add_plugin(pimcommon_ur1cashorturlengineplugin JSON pimcommon_ur1cashorturlengineplugin.json SOURCES
    ${pimcommon_ur1cashorturlengineplugin_SRCS} INSTALL_NAMESPACE pimcommon)

target_link_libraries(pimcommon_ur1cashorturlengineplugin
    KF5::Service KF5::I18n Qt5::Network KF5::CoreAddons shorturlpluginprivate
)

