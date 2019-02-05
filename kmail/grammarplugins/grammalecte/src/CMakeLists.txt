set(kmail_grammalecteplugin_SRCS
    grammalecteparser.cpp
    grammarresultwidget.cpp
    grammarresulttextedit.cpp
    grammalectegrammarerror.cpp
    grammarresultjob.cpp
    grammalecteconfigwidget.cpp
    grammalecteutil.cpp
    grammalectegenerateconfigoptionjob.cpp
    grammalecteconfigdialog.cpp
    )

ecm_qt_declare_logging_category(kmail_grammalecteplugin_SRCS HEADER libgrammalecte_debug.h IDENTIFIER LIBGRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.libgrammalecteplugin)


add_library(libkmailgrammalecte ${kmail_grammalecteplugin_SRCS})
generate_export_header(libkmailgrammalecte BASE_NAME libkmailgrammalecte)
target_link_libraries(libkmailgrammalecte
    KF5::I18n
    KF5::IconThemes
    KF5::ConfigCore
)

set_target_properties(libkmailgrammalecte
    PROPERTIES OUTPUT_NAME libkmailgrammalecte VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )


install(TARGETS libkmailgrammalecte ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
