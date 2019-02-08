set(kmailgrammalecte_SRCS
    grammalecteparser.cpp
    grammarresultjob.cpp
    grammalecteconfigwidget.cpp
    grammalectegenerateconfigoptionjob.cpp
    grammalecteconfigdialog.cpp
    grammalectemanager.cpp
    grammarresultwidget.cpp
    )

ecm_qt_declare_logging_category(kmailgrammalecte_SRCS HEADER libgrammalecte_debug.h IDENTIFIER LIBGRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libgrammalecteplugin)


add_library(kmailgrammalecte ${kmailgrammalecte_SRCS})
generate_export_header(kmailgrammalecte BASE_NAME libkmailgrammalecte)
target_link_libraries(kmailgrammalecte
    KF5::I18n
    KF5::IconThemes
    KF5::ConfigCore
    KF5::WidgetsAddons
    KF5::KIOWidgets
    KF5::MessageComposer
    grammarcommon
)

set_target_properties(kmailgrammalecte
    PROPERTIES OUTPUT_NAME kmailgrammalecte VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )


install(TARGETS kmailgrammalecte ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
