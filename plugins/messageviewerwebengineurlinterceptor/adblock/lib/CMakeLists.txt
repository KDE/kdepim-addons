set(messageviewer_adblock_lib_common_SRCS)
ecm_qt_declare_logging_category(messageviewer_adblock_lib_common_SRCS HEADER adblockinterceptor_debug.h IDENTIFIER ADBLOCKINTERCEPTOR_LOG CATEGORY_NAME log_adblockinterceptor)

set(adblocklibprivate_widget_SRCS
    adblockblockableitemsdialog.cpp
    adblockblockableitemswidget.cpp
    adblockcreatefilterdialog.cpp
    adblockpluginurlinterceptorconfigurewidget.cpp
    )
set(adblocklibprivate_SRCS
    adblockmanager.cpp
    adblocksearchtree.cpp
    adblockrule.cpp
    adblockregexp.cpp
    adblockutil.cpp
    adblockmatcher.cpp
    adblocksubscription.cpp
    ${adblocklibprivate_widget_SRCS}
    ${messageviewer_adblock_lib_common_SRCS}
)
ki18n_wrap_ui(adblocklibprivate_SRCS adblockcreatefilterwidget.ui)

add_library(adblocklibprivate ${adblocklibprivate_SRCS})
generate_export_header(adblocklibprivate BASE_NAME adblocklib)

target_link_libraries(adblocklibprivate
PRIVATE
    Qt5::Core
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    KF5::I18n
    KF5::ItemViews
    KF5::ConfigCore
    KF5::PimCommon
    KF5::MessageViewer
    KF5::KIOWidgets
)

set_target_properties(adblocklibprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS adblocklibprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

add_subdirectory(autotests)
