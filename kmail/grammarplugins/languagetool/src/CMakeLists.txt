set(kmaillanguagetool_SRCS
    languagetoolparser.cpp
)

add_library(kmaillanguagetool ${kmaillanguagetool_SRCS})
generate_export_header(kmaillanguagetool BASE_NAME libkmaillanguagetool)
target_link_libraries(kmaillanguagetool
    KF5::I18n
    KF5::IconThemes
    KF5::ConfigCore
    KF5::WidgetsAddons
    KF5::KIOWidgets
    KF5::MessageComposer
)
