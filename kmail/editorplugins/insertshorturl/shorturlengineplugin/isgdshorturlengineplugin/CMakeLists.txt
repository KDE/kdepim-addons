kcoreaddons_add_plugin(pimcommon_isgdshorturlengineplugin INSTALL_NAMESPACE pim${QT_MAJOR_VERSION}/pimcommon/shorturlengine)
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
    KF${KF_MAJOR_VERSION}::Service KF${KF_MAJOR_VERSION}::I18n Qt::Network KF${KF_MAJOR_VERSION}::CoreAddons shorturlpluginprivate Qt::Gui
    )

