set(pimcommon_isgdshorturlengineplugin_SRCS
    isgdshorturlengineplugin.cpp
    isgdshorturlengineinterface.cpp
    )
ecm_qt_declare_logging_category(pimcommon_isgdshorturlengineplugin_SRCS HEADER isgdshorturlengineplugin_debug.h IDENTIFIER ISGDSHORTURLENGINEPLUGIN_LOG CATEGORY_NAME org.kde.pim.isgdshorturlengineplugin
    DESCRIPTION "kdepim-addons (shorturl engine isgd)"
    OLD_CATEGORY_NAMES log_isgdshorturlengineplugin
    EXPORT KDEPIMADDONS
    )

kcoreaddons_add_plugin(pimcommon_isgdshorturlengineplugin JSON pimcommon_isgdshorturlengineplugin.json SOURCES
    ${pimcommon_isgdshorturlengineplugin_SRCS} INSTALL_NAMESPACE pimcommon/shorturlengine)

target_link_libraries(pimcommon_isgdshorturlengineplugin
    KF5::Service KF5::I18n Qt::Network KF5::CoreAddons shorturlpluginprivate Qt5::Gui
    )

