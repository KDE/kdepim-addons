kcoreaddons_add_plugin(pimcommon_isgdshorturlengineplugin INSTALL_NAMESPACE pimcommon/shorturlengine)
target_sources(pimcommon_isgdshorturlengineplugin PRIVATE
    isgdshorturlengineplugin.cpp
    isgdshorturlengineinterface.cpp
    )
ecm_qt_declare_logging_category(pimcommon_isgdshorturlengineplugin HEADER isgdshorturlengineplugin_debug.h IDENTIFIER ISGDSHORTURLENGINEPLUGIN_LOG CATEGORY_NAME org.kde.pim.isgdshorturlengineplugin
    DESCRIPTION "kdepim-addons (shorturl engine isgd)"
    OLD_CATEGORY_NAMES log_isgdshorturlengineplugin
    EXPORT KDEPIMADDONS
    )


target_link_libraries(pimcommon_isgdshorturlengineplugin
    KF5::Service KF5::I18n Qt${QT_MAJOR_VERSION}::Network KF5::CoreAddons shorturlpluginprivate Qt${QT_MAJOR_VERSION}::Gui
    )

