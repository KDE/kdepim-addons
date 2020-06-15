
add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_vcard_plugin\")

set(messageviewer_bodypartformatter_text_vcard_PART_SRCS text_vcard.cpp vcardmemento.cpp updatecontactjob.cpp)
ecm_qt_declare_logging_category(messageviewer_bodypartformatter_text_vcard_PART_SRCS HEADER vcard_debug.h IDENTIFIER VCARD_LOG CATEGORY_NAME org.kde.pim.vcard
    DESCRIPTION "kdepim-addons (vcard)"
    OLD_CATEGORY_NAMES log_vcard
    EXPORT KDEPIMADDONS
    )


add_library(messageviewer_bodypartformatter_text_vcard MODULE ${messageviewer_bodypartformatter_text_vcard_PART_SRCS})
target_link_libraries(messageviewer_bodypartformatter_text_vcard  KF5::Contacts KF5::PimCommonAkonadi KF5::MessageViewer KF5::IconThemes KF5::JobWidgets KF5::I18n)
install(TARGETS messageviewer_bodypartformatter_text_vcard DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
