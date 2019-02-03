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


add_library(libkmailgrammalect ${kmail_grammalecteplugin_SRCS})
generate_export_header(libkmailgrammalect BASE_NAME libkmailgrammalect)
target_link_libraries(libkmailgrammalect
    KF5::I18n
    KF5::IconThemes
)

set_target_properties(libkmailgrammalect
    PROPERTIES OUTPUT_NAME libkmailgrammalect VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )


install(TARGETS libkmailgrammalect ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

#kcoreaddons_add_plugin(kmail_grammalecteplugin JSON kmail_grammalecteplugin.json SOURCES
#    ${kmail_grammalecteplugin_SRCS} INSTALL_NAMESPACE kmail)

#target_link_libraries(kmail_grammalecteplugin
#        KF5::IconThemes KF5::MessageComposer KF5::I18n KF5::PimCommon libkmailgrammalect
#    )
