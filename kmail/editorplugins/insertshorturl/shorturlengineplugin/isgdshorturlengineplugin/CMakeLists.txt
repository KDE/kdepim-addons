kcoreaddons_add_plugin(pimcommon_isgdshorturlengineplugin INSTALL_NAMESPACE pim6/pimcommon/shorturlengine)
target_sources(
    pimcommon_isgdshorturlengineplugin
    PRIVATE
        isgdshorturlengineplugin.cpp
        isgdshorturlengineinterface.cpp
        isgdshorturlengineplugin.h
        isgdshorturlengineinterface.h
)
ecm_qt_declare_logging_category(pimcommon_isgdshorturlengineplugin HEADER isgdshorturlengineplugin_debug.h IDENTIFIER ISGDSHORTURLENGINEPLUGIN_LOG CATEGORY_NAME org.kde.pim.isgdshorturlengineplugin
    DESCRIPTION "kdepim-addons (shorturl engine isgd)"
    OLD_CATEGORY_NAMES log_isgdshorturlengineplugin
    EXPORT KDEPIMADDONS
)

target_link_libraries(
    pimcommon_isgdshorturlengineplugin
    KF6::Service
    KF6::I18n
    Qt::Network
    KF6::CoreAddons
    shorturlpluginprivate
    Qt::Gui
)
