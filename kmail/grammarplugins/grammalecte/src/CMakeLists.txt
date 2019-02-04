set(kmail_grammalecteplugin_SRCS
    grammalecteparser.cpp
    grammarresultwidget.cpp
    grammarresulttextedit.cpp
    grammalectegrammarerror.cpp
    grammarresultjob.cpp
    grammalecteconfigwidget.cpp
    grammalecteutil.cpp
    )

ecm_qt_declare_logging_category(kmail_grammalecteplugin_SRCS HEADER grammalecteplugin_debug.h IDENTIFIER KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_grammalecteplugin)


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

#kcoreaddons_add_plugin(kmail_grammalecteplugin JSON kmail_grammalecteplugin.json SOURCES
#    ${kmail_grammalecteplugin_SRCS} INSTALL_NAMESPACE kmail)

#target_link_libraries(kmail_grammalecteplugin
#        KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon libkmailgrammalect
#    )
